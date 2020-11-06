{ pkgs ? import <nixpkgs> {} }:
pkgs.mkShell {
  buildInputs = with pkgs; [
    gcc
    cmake
    gnumake
    rocm-opencl-runtime
  ];
}
