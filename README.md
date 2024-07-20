# Digital Frequency Meter

This project implements a digital frequency meter using an Arduino Nano, custom PCB, and supporting components. It measures input frequencies and displays the segments using LED diodes.

## Features

- Measures frequencies from 1 Hz to 1 MHz
- LED segment display for visual output
- Arduino Nano for control and processing
- Custom PCB design for integrated components
- WiFi connectivity for potential remote monitoring

## Hardware Components

- Arduino Nano
- Power supply circuit (±5V)
- Input safety circuitry
- VFC320 for frequency-to-voltage conversion
- ICL7109 for voltage measurement
- MCP23017 I/O expanders for enhanced I/O capabilities
- LED segment display for visual output

## Software

The Arduino code provides the following functionality:
- Frequency measurement
- LED segment control
- Communication with MCP23017 I/O expanders
- Basic WiFi connectivity (configurable)



## PCB Design

The PCB design integrates all necessary components, including:
- Power supply circuitry
- Signal conditioning
- Microcontroller interfacing
- Display drivers



## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

## Acknowledgments

- Project created by Srđan Popadić
- Developed at the University of Novi Sad, Faculty of Technical Sciences
