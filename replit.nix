{ pkgs }: {
	deps = [
		pkgs.clang_12
		pkgs.ccls
		pkgs.gdb
		pkgs.gnumake
    pkgs.glfw
    pkgs.xorg.libX11
    pkgs.libGLU
    pkgs.xorg.xrandr
    pkgs.xorg.xinput
    pkgs.xorg.xinit
    pkgs.glm
	];
}