{
  description = "A flake for development K Power Key Tools";

  inputs.nixpkgs.url = "github:NixOS/nixpkgs/nixos-unstable-small";

  outputs = { self, nixpkgs }: {
    defaultPackage.x86_64-linux =
      with import nixpkgs { system = "x86_64-linux"; };
      stdenv.mkDerivation {
        name = "k_powerk";
        src = ./src;
        buildInputs = [ pkg-config gcc gtk4 ];
        buildPhase =
          "gcc $( pkg-config --cflags gtk4 ) -o k_powerk k_powerk.c $( pkg-config --libs gtk4 )";
        installPhase = "mkdir -p $out/bin; cp k_powerk $out/bin";
      };
  };
}
