; Copyright (c) Future Technology Devices International 2013


; THIS SOFTWARE IS PROVIDED BY FUTURE TECHNOLOGY DEVICES INTERNATIONAL LIMITED ``AS IS'' AND ANY EXPRESS
; OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
; FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL FUTURE TECHNOLOGY DEVICES INTERNATIONAL LIMITED
; BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
; BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
; INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
; (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF
; THE POSSIBILITY OF SUCH DAMAGE.

Objective: 
==========
This generated folder directory contains the converted source from the editor as well as the necessary project dependencies to run on the hardware and FT800 emulator.



Release package contents:
=========================
The folder structure is shown as below.
font
|	\---Bin
|	    \---Msvc_win32
|	    	\--libMPSSE.a - MPSSE library file for connecting to the hardware.
|	    	\--ftd2xx.dll - ftd2xx library file for connecting to the hardware.
|	 
|	    \---MSVC_FT800Emu
|	        \--ft800emu.lib - FT800 Emulator library in release mode
|	        \--ft800emud.ib - FT800 Emulator library in debug mode
|	 
|	\---Hdr
|	    \---\FT_CoPro_Cmds.h  - Includes the FT800 Coprocessor commands.
|	    \---\FT_DataTypes.h - Includes the FT800 datatypes.
|	    \---\FT_Gpu.h - Includes the FT800 commands.
|	    \---\FT_Gpu_Hal.h - Includes the FT800 HAL(Hardware Abstraction Layer) commands.
|	    \---\FT_Hal_Utils.h - Includes the HAL utilities.
|	    \---\FT_Platform.h - Includes Platform specific macros.
|	 
|	    \---Msvc_win32
|	    	\--ftd2xx.h - ftd2xx header file
|	    	\--libMPSSE_spi.h - MPSSE SPI library header file
|	 
|	    \---Msvc_FT800Emu
|	    	\--ft800emu_emulator.h - FT800 emulator header file
|	    	\--ft800emu_inttypes.h - FT800 emulator type definition file
|	        \--FT800Emu_main.h     - C interface for FT800 emulator SPII2C module
|	        \--FT800Emu_spi_i2c.h  - FT800 emulator SPII2C module
|	 
|	    \---Msvc_win32 (MSVC project to run on an actual hardware)
|	        \---font 
|	            \---font.sln - MSVC project solution file.  Double click it will opens up the MSVC C++ IDE, if it's installed.
|	 		    \---font.vcxproj - MSVC project file for the IDE.
|	 			\---font.vcxproj.filter - MSVC project filter file for the IDE.
|	 
|	    \---Msvc_FT800Emu (MSVC project to run on an emulator)
|	        \---font 
|	            \---font.sln - MSVC project solution file.  (FT800 emulator specific)Double click it will opens up the MSVC C++ IDE, if it's installed.
|	 		    \---font.vcxproj - MSVC project filter file for the IDE.
|	 			\---font.vcxproj.filter - MSVC project filter file for the IDE.
|	\---Src
|	    	\---FT_CoPro_Cmds.c - Coprocessor commands source file.
|	    	\---FT_Gpu_Hal.c - Gpu HAL source file.
|	    	\---FT800Emu_main.cpp - The C wrapper of SPI/I2C interface of FT800 emulator and the main() function.
|	        \---font.c - The API implementation of FT800 sample application
|	 
|	\--Test - folder containing input test files such as .wav, .jpg, .raw etc
|
|	\---Readme.txt - This file.
|
|---font.c - copy of the source file of the project.
|
|---(assets).h - copy of the embedded asset data, they can be deleted or use them in somewhere else.



Configuration Instructions:
===========================
This section contains details regarding various configurations supported by this software.

Two display profiles are supported by this software: (1) WQVGA (480x272) (2) QVGA (320x240)

By default WQVGA display profile is enabled. To enable QVGA, disable macro "SAMAPP_DISPLAY_QVGA" and 
enable macro "SAMAPP_DISPLAY_WQVGA" in respective FT_Platform.h file. To enable WQVGA support, please do vice versa. 


To run:
=========================
1] Open the respective font.sln file in the project subfolder for MSVC(MPSSE) platform and MSVC FT800 emulator platform.  
2] Connect the appropriate device to the PC for MSVC(MPSSE) platform.
3] Compile and run the project.


Reference Information:
======================
1. AN_245_VM800CB_SampleApp_PC_Introduction.pdf


Known issues and limitations:
=============================
1. Will work only on SPI mode.
2. The SPI host(Arduino, Windows PC) are assuming the data layout in memory as Little Endian format. 
3. Emulation cannot compile and build MSVC project using the version below Microsoft visual C++ 2012 Express.


