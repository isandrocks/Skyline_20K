# Skyline_20K Project Documentation

## Project Overview

### Purpose and Goals
Skyline_20K is a custom 20-key mechanical keypad/macropad featuring extremely bright RGB underglow lighting. This project combines hardware design, PCB engineering, 3D modeling, and firmware development to create a highly functional and visually striking input device for enthusiasts and power users.

### Problem It Solves
The project addresses several needs in the mechanical keyboard community:
- **Customizable Macro Input**: Provides 20 programmable keys for shortcuts, macros, and special functions
- **Visual Impact**: Features 12 high-intensity 4960 Neopixel LEDs for dramatic underglow effects
- **Modular Design**: Includes breakaway sections that can be snapped off and reconnected, offering flexible form factors
- **Open Source Hardware**: Fully open-source design allows community modifications and learning

### Why It Matters
This project demonstrates the intersection of hardware engineering, firmware development, and maker culture. It showcases:
- Complete end-to-end product development from PCB design to working firmware
- Integration of multiple technologies (USB, RGB lighting, QMK firmware)
- Practical application of microcontroller programming
- Community-driven hardware development practices

## Features & Functionality

### Key Features

#### Hardware Features
1. **20-Key Matrix Layout**: 5×4 grid layout optimized for numpad-style usage and macro programming
2. **Ultra-Bright RGB Lighting**: 
   - 12× 4960 Neopixel LEDs
   - All LEDs face downward for maximum underglow effect
   - Can serve as a functional searchlight due to light intensity
   - Optimized for white 3D-printed cases to maximize light diffusion
3. **Modular PCB Design**:
   - Two breakpoints allow sections to snap off
   - Right-angle header connections for reassembly
   - Detached sections can act as a stand for the keypad
4. **ATmega328P Microcontroller**: Reliable, well-documented 8-bit AVR processor
5. **USB Connectivity**: Direct USB interface using custom bootloader

#### Firmware Features
1. **QMK Firmware Support**: Industry-standard mechanical keyboard firmware
2. **Vial Configuration**: Real-time keymap editing without reflashing
3. **Multiple Layers**: Support for function layers and complex key mappings
4. **RGB Effects**: Pre-configured rainbow mood lighting effect with customizable parameters
5. **N-Key Rollover (NKRO)**: Full anti-ghosting support
6. **Bootmagic**: Configuration features accessible via key combinations

### Technical Highlights

#### Frameworks & Libraries
- **QMK Firmware**: Open-source keyboard firmware framework
- **WS2812 Driver**: Bitbang implementation for LED control with precise timing
- **USBaspLoader**: Custom USB bootloader for AVR microcontrollers
- **Vial**: Real-time keyboard configuration tool

#### Tools & Technologies
- **KiCad**: PCB design and schematic capture
  - Full PCB layout files (`.kicad_pcb`)
  - Schematic files (`.kicad_sch`)
  - Gerber files for manufacturing
- **3D Printing**: STL files for enclosure design (v4 and v7 variants)
- **AVRDUDE**: AVR programming tool for flashing firmware and bootloader
- **USB Protocol**: Custom USB device implementation

### Unique Aspects

1. **Breakaway Design**: Unlike typical keyboards, this features intentional breakpoints for modularity
2. **Extreme Lighting**: The 4960 Neopixel LEDs are significantly brighter than standard WS2812B LEDs
3. **Downward-Facing LEDs**: Unconventional LED orientation creates unique underglow effects
4. **Dual-Purpose Stand**: Broken-off sections serve as a functional stand
5. **Custom USB Bootloader**: Uses USBaspLoader instead of standard Arduino bootloader
6. **Complete Open Source**: Full hardware and firmware files available

## Architecture & Design

### High-Level Structure

The project consists of four main components:

```
Skyline_20K/
├── Hardware Design (KiCad files)
├── Firmware (QMK-based)
├── 3D Models (STL files)
└── Bootloader (USBaspLoader)
```

### Core Components

#### 1. Hardware Layer (PCB Design)
**Files**: `20Key_macropad.kicad_*`, Gerber files
- **Matrix Wiring**: 5 rows × 4 columns = 20 keys
  - Rows: B0, B1, B2, D6, D7
  - Columns: C0, C1, C2, C3
- **Diode Direction**: COL2ROW configuration prevents ghosting
- **LED Controller**: Pin C4 drives the WS2812 LED chain
- **USB Interface**: Native USB pins on ATmega328P
- **Power Management**: USB bus-powered design

**Mechanical Features**:
- Cherry MX compatible switch footprints
- Breakpoints with reinforced traces
- Right-angle header mounting holes
- Mounting holes for case attachment

#### 2. Firmware Layer (QMK)
**Location**: `skyline20k_qmk/`

**Key Files**:
- `config.h`: Hardware configuration and feature settings
- `rules.mk`: Build system configuration and feature flags
- `info.json`: Keyboard metadata and layout definition
- `keymaps/`: Multiple keymap configurations
  - `default/`: Basic functional layout
  - `vial/`: Real-time configurable layout with Vial support

**Configuration Highlights**:
```c
// LED Configuration
#define WS2812_DI_PIN C4      // LED data pin
#define RGBLED_NUM 12          // 12 LEDs total
#define RGBLIGHT_LIMIT_VAL 255 // Maximum brightness

// WS2812 Timing (bitbang driver)
WS2812_TIMING = 1200
WS2812_T1H = 640    // High pulse for '1'
WS2812_T0H = 320    // High pulse for '0'
WS2812_TRST_US = 75 // Reset time
```

#### 3. Bootloader Layer (USBaspLoader)
**Location**: `USBaspLoader/`

- **Purpose**: Allows firmware updates via USB without external programmer
- **Protocol**: Emulates USBasp programmer for compatibility with AVRDUDE
- **Features**:
  - Self-protection from accidental overwrites
  - Update capability for bootloader itself
  - Configurable entry conditions (button/jumper)

**Fuse Settings for ATmega328P**:
```
Low Fuse:  0xFF (16MHz external crystal)
High Fuse: 0xD8 (Bootloader enabled)
Ext Fuse:  0xFF (BOD disabled)
```

#### 4. 3D Model Layer
**Files**: `20Key_macropad v4.stl`, `20Key_macropad v7.stl`
- Designed for white filament to maximize light diffusion
- Multiple versions for iteration and improvements
- Mounting features for PCB attachment
- Provision for breakaway section stand

### Data Flow

1. **Key Press**: Physical switch closes → Matrix scan detects
2. **Processing**: QMK firmware processes → Keymap lookup → USB HID report
3. **USB Communication**: Report sent to host computer
4. **LED Control**: Parallel process drives WS2812 LEDs via bitbang protocol
5. **Configuration**: Vial allows real-time updates via USB without reflashing

### Design Patterns

1. **Matrix Scanning**: Efficient key detection with minimal I/O pins
2. **Interrupt-Driven USB**: Responsive USB communication
3. **State Machine**: LED effects implemented as state machines
4. **Layer System**: Multiple keymap layers for extended functionality
5. **Modular Configuration**: Separated hardware config from behavior logic

## Installation & Setup

### Prerequisites

#### Hardware Requirements
- Skyline_20K PCB (manufactured from Gerber files)
- 20× Cherry MX compatible switches
- 20× Keycaps
- 12× 4960 Neopixel RGB LEDs
- ATmega328P microcontroller (pre-soldered or socketed)
- USB cable (appropriate connector for your design)
- Optional: 3D printed case (STL files provided)

#### Software Requirements
- **QMK Build Environment**: 
  - QMK CLI tools
  - AVR-GCC toolchain
  - ARM GCC (for certain features)
- **AVRDUDE**: For flashing bootloader and firmware
- **Python 3.7+**: Required by QMK CLI
- **Git**: For cloning repositories
- **Optional**: Vial configurator for keymap customization

### Initial Hardware Setup

#### 1. Bootloader Installation
If starting with a blank ATmega328P, you'll need an ISP programmer:

```bash
# Set fuses (enables bootloader, sets clock to external 16MHz)
avrdude -c avrisp -p m328p -P /dev/ttyUSB0 -v -u -U lfuse:w:0xFF:m
avrdude -c avrisp -p m328p -P /dev/ttyUSB0 -v -u -U hfuse:w:0xD8:m
avrdude -c avrisp -p m328p -P /dev/ttyUSB0 -v -u -U efuse:w:0xFF:m

# Flash USBaspLoader
cd USBaspLoader
make DEVICE=atmega328p
make flash
```

**Note**: Replace `/dev/ttyUSB0` with your programmer's port (COM port on Windows).

#### 2. Assembly Steps
1. Solder LEDs to PCB (observe polarity!)
2. Solder switches into PCB
3. Install microcontroller (if socketed) or verify pre-soldered installation
4. Connect USB cable
5. Optional: Snap apart breakaway sections if desired
6. Optional: Install in 3D printed case

### Firmware Setup

#### Building QMK Firmware

1. **Install QMK Environment**:
```bash
# Install QMK CLI
python3 -m pip install --user qmk

# Setup QMK
qmk setup
```

2. **Clone Skyline_20K Repository**:
```bash
git clone https://github.com/isandrocks/Skyline_20K.git
cd Skyline_20K
```

3. **Link Keyboard to QMK**:
```bash
# Create symlink in QMK keyboards directory
ln -s $(pwd)/skyline20k_qmk ~/qmk_firmware/keyboards/skyline20k
```

4. **Build Firmware**:
```bash
# Build default keymap
qmk compile -kb skyline20k -km default

# Or build Vial keymap for real-time configuration
qmk compile -kb skyline20k -km vial
```

#### Flashing Firmware

**Using USBaspLoader** (after initial bootloader installation):
```bash
# Enter bootloader mode (press reset button or configured key combo)
qmk flash -kb skyline20k -km default

# AVRDUDE will automatically detect and flash
```

**Manual AVRDUDE command**:
```bash
avrdude -c usbasp -p m328p -U flash:w:skyline20k_default.hex
```

### Testing

1. **LED Test**: Upon power-up, LEDs should illuminate with default rainbow mood effect
2. **Key Test**: Use a key tester website or text editor to verify all 20 keys respond
3. **Layer Test**: Test function layer keys (if configured)
4. **USB Test**: Verify stable USB connection (no disconnects)

### Vial Configuration (Optional)

1. **Install Vial**:
   - Download from https://get.vial.today/
   - Flash `vial` keymap variant

2. **Configure**:
   - Launch Vial application
   - Connect Skyline_20K
   - Customize keymaps in real-time
   - Adjust RGB settings
   - Save configuration (stored in EEPROM)

## Usage

### Basic Operation

#### Default Keymap (Layer 0)
The default layout is configured as a standard numpad-style layout:
```
ESC   1     2     3
4     5     6     7
8     9     0     BSPC
TAB   Q     W     E
R     T     Y     U
```
(See `skyline20k_qmk/keymaps/default/keymap.c` for complete mapping)

#### Function Layer (Layer 1)
Access by holding the MO(1) key:
- Function keys (F1-F12)
- Arrow keys for navigation
- Volume controls
- Additional media keys

### Example Workflows

#### 1. **Number Pad Entry**
- Use as a dedicated number pad for data entry
- Efficient for spreadsheet work or calculator operations

#### 2. **Macro Programming**
```c
// Example custom macro in keymap.c
case MACRO_1:
    if (record->event.pressed) {
        SEND_STRING("git commit -m \"\"" SS_TAP(X_LEFT));
    }
    return false;
```

#### 3. **Media Control Center**
- Program keys for play/pause, next/previous track
- Volume controls
- Application launching

#### 4. **Gaming Hotkeys**
- Program frequently used game commands
- Quick access to inventory, skills, or macros
- Stream control for content creators

#### 5. **Creative Software Shortcuts**
- Photoshop/GIMP tool selection
- Video editing timeline controls
- 3D modeling shortcuts

### RGB Lighting Control

#### Default Effects
- **Rainbow Mood**: Slowly cycling rainbow effect (enabled by default)
- Brightness: Maximum (255)
- Hue start: 8
- Saturation: Maximum

#### Customizing RGB (via QMK)
Edit `skyline20k_qmk/config.h`:
```c
#define RGBLIGHT_HUE_STEP 8      // Hue change increment
#define RGBLIGHT_SAT_STEP 17     // Saturation change increment
#define RGBLIGHT_VAL_STEP 17     // Brightness change increment
#define RGBLIGHT_LIMIT_VAL 255   // Maximum brightness (reduce if too bright)
```

#### Available RGB Keycodes (add to keymap)
- `RGB_TOG`: Toggle RGB on/off
- `RGB_MOD`: Cycle through effects
- `RGB_HUI/RGB_HUD`: Increase/decrease hue
- `RGB_SAI/RGB_SAD`: Increase/decrease saturation
- `RGB_VAI/RGB_VAD`: Increase/decrease brightness

### Advanced Usage

#### Custom Firmware Modifications
1. Edit keymap in `skyline20k_qmk/keymaps/default/keymap.c`
2. Add custom RGB effects in keymap
3. Implement tap dance or leader key sequences
4. Add custom OLED display support (requires hardware mod)

#### Bootloader Entry
- **Hardware Method**: Short the bootloader entry pins during power-up
- **Software Method**: Configure a key combo to enter bootloader mode
- **Emergency**: Use ISP programmer to force reflash if bootloader corrupted

## Development Notes

### Current Status
- **Hardware**: Prototype completed with minor issues identified
- **PCB Issue**: First prototype had incorrect LED pad layout (documented in README)
- **Firmware**: Functional with QMK and Vial support
- **Case Design**: Multiple STL iterations available (v4, v7)

### Known Issues and Limitations

1. **LED Pad Misalignment** (Prototype v1):
   - Issue: LED pads not properly aligned for 4960 Neopixels
   - Status: Identified, requires PCB revision
   - Workaround: Manual wire connections for prototype testing

2. **Brightness Warning**:
   - 12× 4960 Neopixels at full brightness draw significant current
   - May exceed USB 2.0 500mA limit
   - Recommendation: Limit brightness or use powered USB hub

3. **Bootloader Entry**:
   - Requires physical button or jumper (hardware-dependent)
   - Software bootloader entry would improve user experience

4. **Documentation**:
   - Some documentation files incomplete (placeholders in QMK readme)
   - Assembly instructions could be more detailed

### Planned Improvements

#### Short Term
- [ ] Revise PCB to fix LED pad alignment
- [ ] Complete assembly documentation
- [ ] Add build photos to repository
- [ ] Create step-by-step soldering guide

#### Medium Term
- [ ] Design improved case with better LED diffusion
- [ ] Add rotary encoder support (hardware revision)
- [ ] Implement RGB per-key lighting mode
- [ ] Create configuration web interface
- [ ] Add OLED display support

#### Long Term
- [ ] Wireless variant (Bluetooth/2.4GHz)
- [ ] Hot-swap socket support for switches
- [ ] Split keyboard variant using breakaway design
- [ ] Metal case option for premium version
- [ ] Group buy or small production run

### Development Environment

#### Building from Source
```bash
# Clone repository
git clone https://github.com/isandrocks/Skyline_20K.git
cd Skyline_20K

# Build QMK firmware
cd skyline20k_qmk
qmk compile -kb skyline20k -km default

# Build bootloader (if modifying)
cd ../USBaspLoader
make clean
make DEVICE=atmega328p
```

#### Contributing
This is an open-source project welcoming contributions:
- PCB improvements
- Firmware enhancements
- Case design variations
- Documentation updates
- Bug fixes

### Testing Checklist
- [ ] All 20 keys register correctly
- [ ] No key ghosting in any combination
- [ ] All 12 LEDs illuminate
- [ ] RGB effects run smoothly
- [ ] USB connection stable
- [ ] No excessive heat generation
- [ ] Case fit (if using 3D printed enclosure)
- [ ] Breakaway mechanism works cleanly

## Potential Impact

### Who Benefits

1. **Mechanical Keyboard Enthusiasts**:
   - Custom hardware design inspiration
   - Learning resource for PCB design
   - Platform for experimentation

2. **Content Creators & Streamers**:
   - Quick access to streaming controls
   - Visual indicator for stream status (via RGB)
   - Customizable macro keys for OBS, Discord, etc.

3. **Software Developers**:
   - Programmable shortcuts for IDE functions
   - Git command macros
   - Build/test automation triggers

4. **Designers & Artists**:
   - Quick tool selection in creative software
   - Brush size/opacity controls
   - Timeline navigation shortcuts

5. **Data Entry Professionals**:
   - Dedicated numpad functionality
   - Ergonomic positioning options
   - Reduced hand travel

6. **Students & Educators**:
   - Learning platform for embedded systems
   - Example of complete product development cycle
   - Hands-on electronics and programming project

### Extension Possibilities

#### Hardware Variants
1. **Split Design**: Utilize breakaway feature to create true split numpad
2. **Ortholinear Layout**: Redesign with aligned columns for ergonomics
3. **Macro Pad Series**: 12-key, 16-key, 24-key variants
4. **Display Integration**: Add OLED for status and visual feedback
5. **Encoder Version**: Replace some keys with rotary encoders

#### Software Extensions
1. **Web Configurator**: Browser-based keymap editor
2. **Animation Library**: Pre-made RGB lighting effects
3. **Profile Manager**: Multiple keymap profiles for different applications
4. **Mobile App**: Bluetooth configuration app (for wireless variant)
5. **Integration Plugins**: Direct integration with popular software

#### Alternative Applications
1. **MIDI Controller**: Repurpose as music production tool
2. **Home Automation Interface**: Control smart home devices
3. **Presentation Remote**: Slide control with visual feedback
4. **Accessibility Device**: Custom input device for users with disabilities
5. **Industrial Control**: Simplified control panel for machinery

#### Community Projects
1. **Group Buy Organization**: Community-funded production run
2. **Case Design Contest**: Multiple community-designed enclosures
3. **Firmware Forks**: Specialized firmware variants
4. **Tutorial Series**: Video guides for assembly and programming
5. **Regional Meetups**: Hands-on build workshops

### Educational Value

This project serves as an excellent learning resource for:
- PCB design principles and KiCad workflow
- Embedded C programming
- USB protocol implementation
- AVR microcontroller architecture
- LED driver protocols (WS2812)
- Build system configuration (Makefiles)
- Git version control and collaboration
- Open-source hardware licensing
- Product development lifecycle

### Impact on Maker Community

1. **Knowledge Sharing**: Complete open-source design enables learning and remixing
2. **Lower Barriers**: Makes custom keyboard creation more accessible
3. **Innovation Platform**: Foundation for new ideas and variations
4. **Skill Development**: Real-world project for electronics and firmware skills
5. **Community Building**: Brings together hardware and software enthusiasts

## Additional Resources

### Official Links
- **Main Repository**: https://github.com/isandrocks/Skyline_20K
- **Maintainer**: iSandRocks (https://github.com/iSandRocks)
- **License**: GPL-2.0-or-later (firmware), check individual components for specific licenses

### Documentation & Guides
- **QMK Documentation**: https://docs.qmk.fm/
- **QMK Getting Started**: https://docs.qmk.fm/#/newbs
- **Vial Project**: https://get.vial.today/
- **USBaspLoader Project**: http://matrixstorm.com/avr/tinyusbboard/
- **KiCad Documentation**: https://docs.kicad.org/

### Technical References
- **ATmega328P Datasheet**: https://ww1.microchip.com/downloads/en/DeviceDoc/Atmel-7810-Automotive-Microcontrollers-ATmega328P_Datasheet.pdf
- **WS2812 LED Datasheet**: https://cdn-shop.adafruit.com/datasheets/WS2812.pdf
- **USB HID Specification**: https://www.usb.org/hid
- **AVR-GCC Compiler**: https://gcc.gnu.org/wiki/avr-gcc

### Tools & Software
- **QMK Firmware**: https://github.com/qmk/qmk_firmware
- **Vial**: https://github.com/vial-kb/vial-gui
- **KiCad EDA**: https://www.kicad.org/
- **AVRDUDE**: https://www.nongnu.org/avrdude/
- **PrusaSlicer / Cura**: For 3D printing cases

### Community Resources
- **QMK Discord**: https://discord.gg/qmk
- **r/MechanicalKeyboards**: https://reddit.com/r/MechanicalKeyboards
- **r/olkb**: https://reddit.com/r/olkb (ortholinear/custom keyboards)
- **Deskthority Wiki**: https://deskthority.net/wiki/
- **GeekHack Forums**: https://geekhack.org/

### Learning Resources
- **QMK Tutorial Series**: https://docs.qmk.fm/#/newbs
- **PCB Design Tutorial**: https://www.youtube.com/watch?v=35YuILUlfGs (Contextual Electrons)
- **AVR Programming**: "Make: AVR Programming" by Elliot Williams
- **USB Protocol**: "USB Complete" by Jan Axelson

### Similar Projects for Reference
- **BDN9 Macropad**: 3×3 macropad with RGB underglow
- **MayPad**: Open-source numpad design
- **Sweet16**: 4×4 macropad by 1upkeyboards
- **Discipline**: Through-hole keyboard demonstrating similar techniques

### Manufacturing Resources
- **PCB Fabrication**:
  - JLCPCB: https://jlcpcb.com/
  - PCBWay: https://www.pcbway.com/
  - OSH Park: https://oshpark.com/
- **Components**:
  - Mouser Electronics: https://www.mouser.com/
  - DigiKey: https://www.digikey.com/
  - AliExpress: (for switches, LEDs, keycaps)
- **3D Printing Services**:
  - Shapeways: https://www.shapeways.com/
  - Sculpteo: https://www.sculpteo.com/
  - Local makerspaces and libraries

### File Formats in Repository
- `.kicad_pcb` - PCB layout (open with KiCad)
- `.kicad_sch` - Schematic (open with KiCad)
- `.kicad_pro` - KiCad project file
- `.stl` - 3D model for printing (open with slicer software)
- `.c/.h` - C source and header files (firmware)
- `.json` - Configuration files for QMK/Vial
- `.mk` - Makefile for build system

### Support & Contact
For questions, issues, or contributions:
1. Open an issue on GitHub repository
2. Check existing issues for similar problems
3. Provide detailed information (PCB version, firmware version, steps to reproduce)
4. Include photos for hardware issues

---

**Document Version**: 1.0  
**Last Updated**: 2024  
**Prepared for**: AI Blog Post Generation Agent  
**Project Status**: Active Development, Prototype Stage

This documentation is intended to provide comprehensive context for creating a detailed, informative blog post about the Skyline_20K project. It covers all technical aspects, use cases, and community impact of this open-source hardware project.
