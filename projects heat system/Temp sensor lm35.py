"""
LM35 Temperature Monitor with Arduino Communication
Python GUI for monitoring temperature from Arduino with LM35 sensor
Optimized for screen size: 34.5 cm x 19.4 cm (Approx 1366x768 pixels)
Fixed indicator status issue
"""

import sys
import threading
import time
import re
from datetime import datetime
import numpy as np

from PyQt5 import QtCore, QtWidgets, QtGui
import serial
import serial.tools.list_ports


class SerialReaderThread(QtCore.QThread):
    """Thread for handling serial communication with Arduino"""
    data_received = QtCore.pyqtSignal(float)  # Parsed temperature
    raw_data_received = QtCore.pyqtSignal(str)  # Raw serial data
    error = QtCore.pyqtSignal(str)
    connection_status = QtCore.pyqtSignal(bool)
    message_received = QtCore.pyqtSignal(str)  # For Arduino messages

    def __init__(self, port, baud=9600, parent=None):
        super().__init__(parent)
        self.port = port
        self.baud = baud
        self._stop_event = threading.Event()
        self.ser = None
        self.lock = threading.Lock()

    def run(self):
        """Main thread loop for reading serial data"""
        try:
            self.ser = serial.Serial(
                port=self.port,
                baudrate=self.baud,
                timeout=1,
                write_timeout=1
            )
            time.sleep(2)  # Allow Arduino to reset
            self.connection_status.emit(True)
            self.message_received.emit(f"Connected to {self.port} at {self.baud} baud")
            
        except Exception as e:
            self.error.emit(f"Serial open error: {e}")
            self.connection_status.emit(False)
            return

        buffer = ""
        while not self._stop_event.is_set():
            try:
                if self.ser and self.ser.in_waiting:
                    raw_bytes = self.ser.read(self.ser.in_waiting)
                    
                    try:
                        data = raw_bytes.decode('utf-8', errors='replace')
                    except UnicodeDecodeError:
                        data = raw_bytes.decode('latin-1', errors='replace')
                    
                    self.raw_data_received.emit(data)
                    
                    buffer += data
                    lines = buffer.splitlines(keepends=False)
                    for line in lines[:-1]:
                        line = line.strip()
                        if line:
                            self._process_line(line)
                    
                    buffer = lines[-1] if lines else ""
                else:
                    time.sleep(0.01)
                    
            except serial.SerialException as e:
                self.error.emit(f"Serial error: {e}")
                self.connection_status.emit(False)
                break
            except Exception as e:
                self.error.emit(f"Unexpected error: {e}")
                break

        self.connection_status.emit(False)
        if self.ser and self.ser.is_open:
            try:
                self.ser.close()
            except Exception:
                pass

    def _process_line(self, line):
        """Process a complete line from serial"""
        self.message_received.emit(f"Received: {line}")
        
        pattern = r'[-+]?\d*\.?\d+'
        matches = re.findall(pattern, line)
        
        for match in matches:
            try:
                temp_value = float(match)
                if -55 <= temp_value <= 150:
                    self.data_received.emit(temp_value)
                    return
            except ValueError:
                continue
        
        if "Temperature" in line or "Temp" in line:
            pattern2 = r'[Tt]emp(?:erature)?\s*[:=]\s*([-+]?\d*\.?\d+)'
            match = re.search(pattern2, line)
            if match:
                try:
                    temp_value = float(match.group(1))
                    if -55 <= temp_value <= 150:
                        self.data_received.emit(temp_value)
                except ValueError:
                    pass

    def write_command(self, command):
        """Send a command to Arduino"""
        with self.lock:
            if self.ser and self.ser.is_open:
                try:
                    if not command.endswith('\n'):
                        command += '\n'
                    self.ser.write(command.encode('utf-8'))
                    self.message_received.emit(f"Sent: {command.strip()}")
                    return True
                except Exception as e:
                    self.error.emit(f"Write error: {e}")
                    return False
            return False

    def stop(self):
        """Stop the thread"""
        self._stop_event.set()
        self.wait()


class TemperatureData:
    """Class to manage temperature history and statistics"""
    def __init__(self, max_history=200):
        self.temperatures = []
        self.timestamps = []
        self.max_history = max_history
        
    def add_reading(self, temperature):
        """Add a new temperature reading"""
        self.temperatures.append(temperature)
        self.timestamps.append(datetime.now())
        
        if len(self.temperatures) > self.max_history:
            self.temperatures.pop(0)
            self.timestamps.pop(0)
    
    def get_stats(self):
        """Calculate statistics from recent readings"""
        if not self.temperatures:
            return None
        
        recent_temps = self.temperatures[-50:] if len(self.temperatures) > 50 else self.temperatures
        temps_array = np.array(recent_temps)
        
        return {
            'current': self.temperatures[-1] if self.temperatures else None,
            'average': float(np.mean(temps_array)),
            'min': float(np.min(temps_array)),
            'max': float(np.max(temps_array)),
            'std': float(np.std(temps_array)),
            'count': len(self.temperatures)
        }


class TempMonitorApp(QtWidgets.QWidget):
    """Main application window for temperature monitoring"""
    def __init__(self):
        super().__init__()
        self.setWindowTitle("LM35 Temperature Monitor")
        
        # Set window size for 34.5cm x 19.4cm screen (~1280x720 effective area)
        self.resize(1280, 720)
        
        # Initialize variables
        self.serial_thread = None
        self.temp_data = TemperatureData(max_history=200)
        self.alarm_threshold = 60.0
        self.connection_active = False
        self.buzzer_flashing = False
        
        # Store LED colors for each indicator
        self.led_colors = {
            'green': '#00FF00',  # Bright green
            'red': '#FF0000',    # Bright red
            'yellow': '#FFFF00'  # Bright yellow
        }
        
        # Setup UI
        self._build_ui()
        self._setup_timers()
        
        # Populate ports on startup
        QtCore.QTimer.singleShot(100, self._populate_ports)

    def _build_ui(self):
        """Build the user interface optimized for screen size"""
        main_layout = QtWidgets.QVBoxLayout(self)
        main_layout.setContentsMargins(8, 8, 8, 8)
        main_layout.setSpacing(8)
        
        # ===== TOP ROW: Connection and Control =====
        top_row = QtWidgets.QHBoxLayout()
        
        # Connection Panel - Compact version
        connection_group = QtWidgets.QGroupBox("Connection")
        connection_layout = QtWidgets.QGridLayout(connection_group)
        connection_group.setMaximumHeight(120)
        
        # Port selection
        connection_layout.addWidget(QtWidgets.QLabel("Port:"), 0, 0)
        self.port_combo = QtWidgets.QComboBox()
        self.port_combo.setMinimumWidth(180)
        connection_layout.addWidget(self.port_combo, 0, 1)
        
        self.refresh_btn = QtWidgets.QPushButton("↻")
        self.refresh_btn.setFixedWidth(40)
        self.refresh_btn.setToolTip("Refresh ports")
        self.refresh_btn.clicked.connect(self._populate_ports)
        connection_layout.addWidget(self.refresh_btn, 0, 2)
        
        # Baud rate selection
        connection_layout.addWidget(QtWidgets.QLabel("Baud:"), 1, 0)
        self.baud_combo = QtWidgets.QComboBox()
        self.baud_combo.addItems(['9600', '19200', '38400', '57600', '115200'])
        self.baud_combo.setCurrentText('9600')
        connection_layout.addWidget(self.baud_combo, 1, 1)
        
        # Connection button
        self.connect_btn = QtWidgets.QPushButton("Connect")
        self.connect_btn.setFixedWidth(100)
        self.connect_btn.clicked.connect(self._toggle_connection)
        self.connect_btn.setStyleSheet("""
            QPushButton {
                background-color: #4CAF50;
                color: white;
                font-weight: bold;
                padding: 6px;
                border-radius: 4px;
            }
            QPushButton:hover {
                background-color: #45a049;
            }
        """)
        connection_layout.addWidget(self.connect_btn, 1, 2)
        
        # Status indicator
        self.status_indicator = QtWidgets.QLabel("● Disconnected")
        self.status_indicator.setFont(QtGui.QFont("Arial", 9))
        self._update_status_indicator(False)
        connection_layout.addWidget(self.status_indicator, 0, 3, 2, 1)
        
        top_row.addWidget(connection_group)
        
        # Control Panel - Compact version
        control_group = QtWidgets.QGroupBox("Alarm Control")
        control_layout = QtWidgets.QVBoxLayout(control_group)
        control_group.setMaximumHeight(120)
        
        threshold_layout = QtWidgets.QHBoxLayout()
        threshold_layout.addWidget(QtWidgets.QLabel("Threshold:"))
        
        self.threshold_slider = QtWidgets.QSlider(QtCore.Qt.Horizontal)
        self.threshold_slider.setRange(0, 100)
        self.threshold_slider.setValue(60)
        self.threshold_slider.setTickPosition(QtWidgets.QSlider.TicksBelow)
        self.threshold_slider.setTickInterval(10)
        self.threshold_slider.valueChanged.connect(self._on_slider_changed)
        threshold_layout.addWidget(self.threshold_slider)
        
        self.threshold_spin = QtWidgets.QDoubleSpinBox()
        self.threshold_spin.setFixedWidth(80)
        self.threshold_spin.setRange(0, 100)
        self.threshold_spin.setValue(60.0)
        self.threshold_spin.setSingleStep(0.5)
        self.threshold_spin.setSuffix(" °C")
        self.threshold_spin.valueChanged.connect(self._update_threshold)
        threshold_layout.addWidget(self.threshold_spin)
        
        control_layout.addLayout(threshold_layout)
        
        self.send_threshold_btn = QtWidgets.QPushButton("Send to Arduino")
        self.send_threshold_btn.clicked.connect(self._send_threshold_to_arduino)
        self.send_threshold_btn.setEnabled(False)
        control_layout.addWidget(self.send_threshold_btn)
        
        top_row.addWidget(control_group)
        
        main_layout.addLayout(top_row)
        
        # ===== CENTER ROW: Temperature Display and Indicators =====
        center_row = QtWidgets.QHBoxLayout()
        
        # Large Temperature Display
        temp_group = QtWidgets.QGroupBox("Temperature")
        temp_layout = QtWidgets.QVBoxLayout(temp_group)
        
        self.temp_display = QtWidgets.QLabel("-- °C")
        self.temp_display.setFont(QtGui.QFont("Arial", 64, QtGui.QFont.Bold))
        self.temp_display.setAlignment(QtCore.Qt.AlignCenter)
        self.temp_display.setStyleSheet("color: #333; padding: 20px;")
        temp_layout.addWidget(self.temp_display)
        
        center_row.addWidget(temp_group, 2)  # 2/3 of width
        
        # Status Indicators
        indicators_group = QtWidgets.QGroupBox("Status")
        indicators_layout = QtWidgets.QVBoxLayout(indicators_group)
        indicators_group.setMaximumWidth(300)
        
        # Store LED references
        self.leds = {}
        
        # Normal indicator
        normal_widget = self._create_indicator_widget("NORMAL", "green")
        self.green_led = normal_widget.findChild(QtWidgets.QLabel, "led")
        self.leds['green'] = self.green_led
        indicators_layout.addWidget(normal_widget)
        
        # Alarm indicator
        alarm_widget = self._create_indicator_widget("ALARM", "red")
        self.red_led = alarm_widget.findChild(QtWidgets.QLabel, "led")
        self.leds['red'] = self.red_led
        indicators_layout.addWidget(alarm_widget)
        
        # Buzzer indicator
        buzzer_widget = self._create_indicator_widget("BUZZER", "yellow")
        self.buzzer_led = buzzer_widget.findChild(QtWidgets.QLabel, "led")
        self.leds['yellow'] = self.buzzer_led
        indicators_layout.addWidget(buzzer_widget)
        
        center_row.addWidget(indicators_group, 1)  # 1/3 of width
        
        main_layout.addLayout(center_row)
        
        # ===== BOTTOM ROW: Data and Statistics =====
        bottom_row = QtWidgets.QHBoxLayout()
        
        # Raw Serial Data Display
        raw_data_group = QtWidgets.QGroupBox("Raw Serial Data")
        raw_data_layout = QtWidgets.QVBoxLayout(raw_data_group)
        
        self.raw_data_display = QtWidgets.QTextEdit()
        self.raw_data_display.setMaximumHeight(150)
        self.raw_data_display.setReadOnly(True)
        self.raw_data_display.setFont(QtGui.QFont("Courier", 9))
        self.raw_data_display.setStyleSheet("""
            QTextEdit {
                background-color: #000;
                color: #0F0;
                border: 1px solid #333;
                font-size: 10px;
            }
        """)
        raw_data_layout.addWidget(self.raw_data_display)
        
        # Control buttons for raw data
        raw_controls_layout = QtWidgets.QHBoxLayout()
        self.clear_raw_btn = QtWidgets.QPushButton("Clear")
        self.clear_raw_btn.clicked.connect(self._clear_raw_data)
        raw_controls_layout.addWidget(self.clear_raw_btn)
        
        self.pause_raw_btn = QtWidgets.QPushButton("Pause")
        self.pause_raw_btn.setCheckable(True)
        self.pause_raw_btn.clicked.connect(self._toggle_raw_pause)
        raw_controls_layout.addWidget(self.pause_raw_btn)
        
        raw_controls_layout.addStretch()
        raw_data_layout.addLayout(raw_controls_layout)
        
        bottom_row.addWidget(raw_data_group, 1)
        
        # Statistics Panel
        stats_group = QtWidgets.QGroupBox("Statistics")
        stats_layout = QtWidgets.QGridLayout(stats_group)
        
        self.stats_labels = {}
        stats_info = [
            ('current', 'Current:'),
            ('average', 'Average:'),
            ('min', 'Minimum:'),
            ('max', 'Maximum:'),
            ('std', 'Std Dev:'),
            ('readings', 'Readings:')
        ]
        
        for i, (key, label_text) in enumerate(stats_info):
            row = i
            col = 0
            
            label = QtWidgets.QLabel(label_text)
            label.setFont(QtGui.QFont("Arial", 9))
            stats_layout.addWidget(label, row, col)
            
            value_label = QtWidgets.QLabel("--")
            value_label.setFont(QtGui.QFont("Arial", 9, QtGui.QFont.Bold))
            value_label.setAlignment(QtCore.Qt.AlignRight)
            stats_layout.addWidget(value_label, row, col + 1)
            self.stats_labels[key] = value_label
        
        bottom_row.addWidget(stats_group, 1)
        
        main_layout.addLayout(bottom_row)
        
        # ===== MESSAGE LOG =====
        log_group = QtWidgets.QGroupBox("Messages")
        log_layout = QtWidgets.QVBoxLayout(log_group)
        
        self.message_log = QtWidgets.QTextEdit()
        self.message_log.setMaximumHeight(100)
        self.message_log.setReadOnly(True)
        self.message_log.setFont(QtGui.QFont("Courier", 9))
        self.message_log.setStyleSheet("""
            QTextEdit {
                background-color: #f8f8f8;
                border: 1px solid #ddd;
                font-size: 10px;
            }
        """)
        log_layout.addWidget(self.message_log)
        
        # Log controls
        log_controls_layout = QtWidgets.QHBoxLayout()
        self.clear_log_btn = QtWidgets.QPushButton("Clear")
        self.clear_log_btn.clicked.connect(self._clear_message_log)
        log_controls_layout.addWidget(self.clear_log_btn)
        
        self.pause_log_btn = QtWidgets.QPushButton("Pause")
        self.pause_log_btn.setCheckable(True)
        self.pause_log_btn.clicked.connect(self._toggle_log_pause)
        log_controls_layout.addWidget(self.pause_log_btn)
        
        log_controls_layout.addStretch()
        log_layout.addLayout(log_controls_layout)
        
        main_layout.addWidget(log_group)
        
        # ===== STATUS BAR =====
        self.status_bar = QtWidgets.QLabel("Ready to connect")
        self.status_bar.setFrameStyle(QtWidgets.QFrame.Panel | QtWidgets.QFrame.Sunken)
        self.status_bar.setStyleSheet("""
            padding: 3px;
            background-color: #f0f0f0;
            font-size: 10px;
        """)
        main_layout.addWidget(self.status_bar)
        
        # Variables for pausing displays
        self.raw_data_paused = False
        self.log_paused = False
        self.paused_raw_data = ""
        self.paused_messages = []

    def _create_indicator_widget(self, label_text, color_name):
        """Create an indicator widget with LED"""
        widget = QtWidgets.QWidget()
        layout = QtWidgets.QHBoxLayout(widget)
        layout.setContentsMargins(5, 5, 5, 5)
        layout.setSpacing(10)
        
        label = QtWidgets.QLabel(label_text)
        label.setFont(QtGui.QFont("Arial", 10, QtGui.QFont.Bold))
        label.setFixedWidth(80)
        layout.addWidget(label)
        
        led = QtWidgets.QLabel()
        led.setObjectName("led")
        led.setFixedSize(30, 30)
        led.setStyleSheet(f"""
            background-color: grey;
            border-radius: 15px;
            border: 2px solid #333;
        """)
        layout.addWidget(led)
        
        # Store the color name as a property
        led.setProperty("color_name", color_name)
        
        return widget

    def _setup_timers(self):
        """Setup timers for periodic updates"""
        self.stats_timer = QtCore.QTimer()
        self.stats_timer.timeout.connect(self._update_statistics)
        self.stats_timer.start(1000)
        
        self.ui_timer = QtCore.QTimer()
        self.ui_timer.timeout.connect(self._update_ui_state)
        self.ui_timer.start(100)

    def _populate_ports(self):
        """Populate the COM port dropdown"""
        self.port_combo.clear()
        ports = list(serial.tools.list_ports.comports())
        
        if ports:
            for port in ports:
                description = port.description if port.description else "Unknown"
                self.port_combo.addItem(f"{port.device} - {description}", port.device)
        else:
            self.port_combo.addItem("No COM ports found", "")

    def _toggle_connection(self):
        """Toggle serial connection"""
        if self.connection_active:
            self._disconnect()
        else:
            self._connect()

    def _connect(self):
        """Establish serial connection"""
        if self.port_combo.currentData() is None or self.port_combo.currentData() == "":
            self.status_bar.setText("Please select a valid COM port")
            return
        
        port = self.port_combo.currentData()
        
        try:
            baud = int(self.baud_combo.currentText())
        except ValueError:
            baud = 9600
        
        self.serial_thread = SerialReaderThread(port, baud)
        self.serial_thread.data_received.connect(self._update_temperature)
        self.serial_thread.raw_data_received.connect(self._update_raw_data)
        self.serial_thread.error.connect(self._handle_error)
        self.serial_thread.connection_status.connect(self._update_status_indicator)
        self.serial_thread.message_received.connect(self._log_message)
        self.serial_thread.start()
        
        self.connection_active = True
        self.connect_btn.setText("Disconnect")
        self.connect_btn.setStyleSheet("""
            QPushButton {
                background-color: #f44336;
                color: white;
                font-weight: bold;
                padding: 6px;
                border-radius: 4px;
            }
            QPushButton:hover {
                background-color: #d32f2f;
            }
        """)
        self.send_threshold_btn.setEnabled(True)
        
        QtCore.QTimer.singleShot(1000, self._send_threshold_to_arduino)

    def _disconnect(self):
        """Disconnect serial connection"""
        if self.serial_thread:
            self.serial_thread.stop()
            self.serial_thread = None
        
        self.connection_active = False
        self.connect_btn.setText("Connect")
        self.connect_btn.setStyleSheet("""
            QPushButton {
                background-color: #4CAF50;
                color: white;
                font-weight: bold;
                padding: 6px;
                border-radius: 4px;
            }
            QPushButton:hover {
                background-color: #45a049;
            }
        """)
        self.send_threshold_btn.setEnabled(False)
        self._update_status_indicator(False)
        
        self.temp_display.setText("-- °C")
        self.temp_display.setStyleSheet("color: #333;")
        self._set_led_state(self.green_led, False)
        self._set_led_state(self.red_led, False)
        self._set_led_state(self.buzzer_led, False)

    def _update_temperature(self, temp_c):
        """Handle incoming temperature data"""
        self.temp_data.add_reading(temp_c)
        
        self.temp_display.setText(f"{temp_c:.1f} °C")
        
        is_alarm = temp_c >= self.alarm_threshold
        
        # Update indicator states
        self._set_led_state(self.green_led, not is_alarm)
        self._set_led_state(self.red_led, is_alarm)
        
        if is_alarm:
            # Alarm state - red and buzzer ON, green OFF
            self._set_led_state(self.green_led, False)
            self._set_led_state(self.red_led, True)
            self._set_led_state(self.buzzer_led, True)
            self.temp_display.setStyleSheet("color: red; font-size: 64px;")
            
            if not self.buzzer_flashing:
                self._start_buzzer_flash()
        else:
            # Normal state - green ON, red and buzzer OFF
            self._set_led_state(self.green_led, True)
            self._set_led_state(self.red_led, False)
            self._set_led_state(self.buzzer_led, False)
            self.temp_display.setStyleSheet("color: #333; font-size: 64px;")
            self.buzzer_flashing = False

    def _update_raw_data(self, raw_data):
        """Update raw serial data display"""
        if self.raw_data_paused:
            self.paused_raw_data += raw_data
            return
        
        display_data = raw_data.replace('\r', '␍').replace('\n', '␊\n')
        
        current_text = self.raw_data_display.toPlainText()
        
        if len(current_text) > 2000:
            current_text = current_text[-2000:]
        
        new_text = current_text + display_data
        self.raw_data_display.setText(new_text)
        
        self.raw_data_display.verticalScrollBar().setValue(
            self.raw_data_display.verticalScrollBar().maximum()
        )

    def _set_led_state(self, led, is_on):
        """Set LED on/off state with the correct color"""
        if is_on:
            # Get the color name from the LED's property
            color_name = led.property("color_name")
            if color_name in self.led_colors:
                color = self.led_colors[color_name]
            else:
                color = self.led_colors.get('green', '#00FF00')
                
            led.setStyleSheet(f"""
                background-color: {color};
                border-radius: 15px;
                border: 2px solid #333;
            """)
        else:
            led.setStyleSheet("""
                background-color: #808080;
                border-radius: 15px;
                border: 2px solid #333;
            """)

    def _start_buzzer_flash(self):
        """Start buzzer flashing effect"""
        self.buzzer_flashing = True
        self.flash_counter = 0
        self.flash_timer = QtCore.QTimer()
        self.flash_timer.timeout.connect(self._update_buzzer_flash)
        self.flash_timer.start(300)  # Flash every 300ms

    def _update_buzzer_flash(self):
        """Update buzzer flash animation"""
        if not self.buzzer_flashing:
            self.flash_timer.stop()
            return
        
        if self.flash_counter >= 40:  # Flash for 12 seconds (40 * 0.3s)
            # Reset counter to continue flashing while alarm is active
            self.flash_counter = 0
        
        # Alternate between yellow and grey
        if self.flash_counter % 2 == 0:
            self.buzzer_led.setStyleSheet(f"""
                background-color: {self.led_colors['yellow']};
                border-radius: 15px;
                border: 2px solid #333;
            """)
        else:
            self.buzzer_led.setStyleSheet("""
                background-color: #808080;
                border-radius: 15px;
                border: 2px solid #333;
            """)
        
        self.flash_counter += 1

    def _update_threshold(self, value):
        """Update alarm threshold"""
        self.alarm_threshold = value
        self.threshold_slider.setValue(int(value))
        
        self.status_bar.setText(f"Alarm threshold set to {value}°C")
        
        stats = self.temp_data.get_stats()
        if stats and stats['current'] is not None:
            self._update_temperature(stats['current'])

    def _on_slider_changed(self, value):
        """Handle slider value change"""
        self.threshold_spin.setValue(float(value))

    def _send_threshold_to_arduino(self):
        """Send current threshold to Arduino"""
        if self.serial_thread and self.connection_active:
            command = f"THRESHOLD={self.alarm_threshold:.1f}"
            success = self.serial_thread.write_command(command)
            
            if success:
                self.status_bar.setText(f"Threshold {self.alarm_threshold}°C sent to Arduino")
            else:
                self.status_bar.setText("Failed to send threshold to Arduino")

    def _update_statistics(self):
        """Update statistics display"""
        stats = self.temp_data.get_stats()
        if stats:
            self.stats_labels['current'].setText(f"{stats['current']:.1f} °C")
            self.stats_labels['average'].setText(f"{stats['average']:.1f} °C")
            self.stats_labels['min'].setText(f"{stats['min']:.1f} °C")
            self.stats_labels['max'].setText(f"{stats['max']:.1f} °C")
            self.stats_labels['std'].setText(f"{stats['std']:.3f} °C")
            self.stats_labels['readings'].setText(str(stats['count']))

    def _update_ui_state(self):
        """Periodic UI state updates"""
        if self.serial_thread and self.serial_thread.isRunning():
            if not self.connection_active:
                self.connection_active = True
                self.connect_btn.setText("Disconnect")
        elif self.connection_active:
            self.connection_active = False
            self.connect_btn.setText("Connect")

    def _update_status_indicator(self, connected):
        """Update connection status indicator"""
        if connected:
            self.status_indicator.setText("● Connected")
            self.status_indicator.setStyleSheet("color: green; font-weight: bold;")
        else:
            self.status_indicator.setText("● Disconnected")
            self.status_indicator.setStyleSheet("color: red;")

    def _log_message(self, message):
        """Add message to log display"""
        if self.log_paused:
            self.paused_messages.append(message)
            return
        
        timestamp = datetime.now().strftime("%H:%M:%S")
        log_entry = f"[{timestamp}] {message}"
        
        current_text = self.message_log.toPlainText()
        lines = current_text.split('\n')
        
        if len(lines) > 30:
            lines = lines[-30:]
        
        lines.append(log_entry)
        self.message_log.setText('\n'.join(lines))
        
        self.message_log.verticalScrollBar().setValue(
            self.message_log.verticalScrollBar().maximum()
        )

    def _clear_raw_data(self):
        """Clear the raw data display"""
        self.raw_data_display.clear()
        self.paused_raw_data = ""

    def _clear_message_log(self):
        """Clear the message log"""
        self.message_log.clear()
        self.paused_messages = []

    def _toggle_raw_pause(self):
        """Toggle pause state for raw data"""
        self.raw_data_paused = self.pause_raw_btn.isChecked()
        
        if self.raw_data_paused:
            self.pause_raw_btn.setText("Resume")
            self.pause_raw_btn.setStyleSheet("background-color: #ff9800; color: white;")
        else:
            self.pause_raw_btn.setText("Pause")
            self.pause_raw_btn.setStyleSheet("")
            if self.paused_raw_data:
                self._update_raw_data(self.paused_raw_data)
                self.paused_raw_data = ""

    def _toggle_log_pause(self):
        """Toggle pause state for message log"""
        self.log_paused = self.pause_log_btn.isChecked()
        
        if self.log_paused:
            self.pause_log_btn.setText("Resume")
            self.pause_log_btn.setStyleSheet("background-color: #ff9800; color: white;")
        else:
            self.pause_log_btn.setText("Pause")
            self.pause_log_btn.setStyleSheet("")
            if self.paused_messages:
                for msg in self.paused_messages:
                    self._log_message(msg)
                self.paused_messages = []

    def _handle_error(self, error_msg):
        """Handle error messages"""
        self.status_bar.setText(f"Error: {error_msg}")
        self._log_message(f"ERROR: {error_msg}")

    def closeEvent(self, event):
        """Handle application close"""
        self._disconnect()
        
        if hasattr(self, 'stats_timer'):
            self.stats_timer.stop()
        if hasattr(self, 'ui_timer'):
            self.ui_timer.stop()
        if hasattr(self, 'flash_timer'):
            self.flash_timer.stop()
        
        event.accept()


def main():
    """Main application entry point"""
    app = QtWidgets.QApplication(sys.argv)
    
    app.setStyle('Fusion')
    
    # Set font sizes appropriate for screen size
    font = QtGui.QFont()
    font.setFamily("Segoe UI")
    font.setPointSize(10)
    app.setFont(font)
    
    window = TempMonitorApp()
    window.show()
    
    sys.exit(app.exec_())


if __name__ == "__main__":
    main()