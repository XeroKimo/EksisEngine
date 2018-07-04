# EksisEngine
Small project for students

Everyone will have a minimum of 2 versions of control

Stable: Is shareable, must be updated when your current goal has been reached, or part of it.
	
	Eg: I want to make an input system that can handle controllers, mouse and keyboard. I can update it once I'm satisfied with my mouse structure, or I can wait 'till I finish all 3 systems.
	Note: Do not update it if you’re planning to change the structure. No structure updates should be pushed in stable unless you’re abstracting functionality or adding functionality from said structure
	Optional: Put all changed and new header/cpp files in a separate build so people can quickly drag stable changes into their folder

Experimental: Do whatever the fuck you want
	
	Note: Document any major functionality or requested functionality. Also document added files and files that were changed or deleted


It appears that library linking doesn't carry over, if that's the caase, make sure to include d3d11.lib, D3DCompiler.lib and Windowscodecs.lib
