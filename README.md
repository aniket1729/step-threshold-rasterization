**** CG Lines — Computer Graphics Algorithms in C++ ****

A collection of Computer Graphics algorithms implemented in C++, with a live graphics window rendered using Python and Pygame Community Edition (Pygame-CE).

The project currently implements the Step-Threshold Line Drawing Algorithm, supporting shallow lines, steep lines, negative slopes, and all eight octants.

**** Features
	#) C++ implementation of the Step-Threshold line drawing algorithm.
	#) Live graphics window using Pygame-CE.
	#) Different colours for different lines.
	#) Python virtual environment for dependency isolation.
	#) No requirement for graphics.h, conio.h, SDL development headers, or CMake.
	#) Suitable for remote Linux systems with graphical display forwarding.

**** Project Structure
	cg_lines/
	├── main.cpp          # C++ line-drawing algorithm
	├── viewer.py         # Pygame graphics viewer
	├── compile_run.sh    #
	├── pyproject.toml    # Python project configuration
	├── .gitignore        # Files excluded from Git
	├── README.md         # Project documentation
	└── prototypes/
	    ├── evolutionary_prototypes.cpp    #
	    └── empirical_testing.cpp          #

**** Requirements
	#) Linux (Ubuntu/Debian recommended).
	#) Python 3.10 or newer.
	#) A C++ compiler supporting C++17, such as g++.
	#) Git.
	#) Internet access to install Python dependencies.
	#) A graphical display for the Pygame window.

For remote Linux servers accessed through SSH, X11 forwarding must be configured if the graphics window is to appear on your local computer.

**** 1. Download the Project
	Clone the repository:
	$ git clone <YOUR_GITHUB_REPOSITORY_URL>
	$ cd cg_lines

	Replace <YOUR_GITHUB_REPOSITORY_URL> with the HTTPS or SSH URL of your GitHub repository.
	Alternatively, download the repository as a ZIP file from GitHub and extract it.

**** 2. Create a Python Virtual Environment
	Create an isolated environment:
    user@machine:~/cg_lines$ python3 -m venv .venv

	Activate it:
	user@machine:~/cg_lines$ source .venv/bin/activate

	Your terminal should now show the virtual environment name, for example:
	(.venv) user@machine:~/cg_lines$

**** 3. Install Python Dependencies
	Upgrade pip:
	$ python -m pip install --upgrade pip

	Install the project and its dependencies:
	$ python -m pip install -e .

	The required Python graphics dependency, Pygame-CE, is declared in pyproject.toml.
	No administrator privileges are required for installation inside the virtual environment, provided compatible packages and runtime libraries are available.

**** 4. Compile the C++ Program
	Compile main.cpp using g++:
	$ g++ -std=c++17 -Wall -Wextra main.cpp -o cg_lines

	This creates an executable named cg_lines in the project directory.

**** 5. Run the Program
	Start the graphics viewer:
	$ python viewer.py

	The viewer runs the C++ executable, reads its drawing commands, and displays the lines in a Pygame window.
	Press Esc or close the window to exit.

**** 6. Expected Output
	The graphics window displays three lines:
		#) Shallow line: (100,100) to (280,120) — white.
		#) Steep line: (100,100) to (120,200) — yellow.
		#) Negative-slope line: (100,150) to (150,100) — light green.

	The terminal prints the corresponding line descriptions from the C++ program.

**** 7. Running on a Remote Linux Server
	If the program runs on a remote Linux machine and you want the window to appear on your local computer, connect through SSH with X11 forwarding enabled.

	For example, from your local terminal:
	$ ssh -X username@hostname
	If trusted forwarding is required and permitted by the server administrator, ssh -Y may also be used.

	Check the display variable:
	$ echo $DISPLAY

	Test graphical forwarding, if xclock is installed:
	$ xclock
	If the clock window appears locally, X11 forwarding is working.
	Then activate the virtual environment, compile the C++ program, and run the Python viewer as described above.

	Note: X11 forwarding requires a compatible local X server on Windows, macOS, or another client system, along with server-side SSH forwarding support. The DISPLAY variable alone does not guarantee that every graphics application will work.

**** 8. Troubleshooting
	g++: command not found
		Install or request access to a C++ compiler. On Ubuntu/Debian, the system package is usually build-essential.

	ModuleNotFoundError: No module named 'pygame'
		Activate the virtual environment and reinstall the project:
		$ source .venv/bin/activate
		$ python -m pip install -e .

	FileNotFoundError: ./cg_lines
		Compile the C++ source first:
		$ g++ -std=c++17 -Wall -Wextra main.cpp -o cg_lines

	pygame.error: ... No available video device
		The graphics display is unavailable or incorrectly configured. Check your local display server, SSH X11 forwarding, and the DISPLAY environment variable.

	Missing SDL shared library
		Pygame requires compatible SDL runtime libraries. Installing Python packages may not be sufficient if the operating system lacks required native libraries. Consult the system administrator if the missing library cannot be supplied within your permitted environment.

**** 9. Development Workflow
	After editing the C++ algorithm, recompile it:
		$ g++ -std=c++17 -Wall -Wextra main.cpp -o cg_lines

	Then launch the viewer:
		$ python viewer.py

	The executable is generated locally and does not need to be committed to Git.

**** 10. Git Ignore Rules
	The .gitignore file should contain:
		.venv/
		__pycache__/
		*.py[cod]
		*.egg-info/
		cg_lines

	This excludes the virtual environment, generated Python files, package metadata, and compiled executable while keeping the source code and configuration files in version control.

**** Future Extensions
	Possible additions include:
		#) Digital Differential Analyzer (DDA) line drawing.
		#) Bresenham's line drawing algorithm.
		#) Midpoint circle drawing algorithm.
		#) Ellipse drawing.
		#) Polygon filling algorithms.
		#) Step-by-step algorithm visualisation.

**** License
	Open License
