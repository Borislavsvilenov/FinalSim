{
  description = "Particle Simulations";

  inputs = {
    flake-utils.url = "github:numtide/flake-utils";
  };

  outputs = { self, nixpkgs, flake-utils }: {
    overlays.default = final: prev: {
      grav = final.callPackage ({stdenv, pkgs, ...}:
        stdenv.mkDerivation {
          src = ./.;
          pname = "Gravity";
          version = "unstable";
          nativeBuildInputs = with pkgs; [ cmake ];
          buildInputs = with pkgs; [
            raylib
          ];
          
          cmakeFlags = [ "-DCMAKE_PREFIX_PATH=${pkgs.raylib}" ];

          installPhase = ''
            mkdir -p $out/bin
            cp $pname $out/bin/Gravity
          '';
        }
      ) {};
    };
  } // 
  (flake-utils.lib.eachDefaultSystem (system:
    let
      pkgs = import nixpkgs {
        system = system;
        overlays = [ self.overlays.default ];
      };
      lib = nixpkgs.lib;
    in
      {
        packages = {
          grav = pkgs.grav;
          default = self.packages.${system}.grav;
        };

        devShells.default = pkgs.mkShell {
          buildInputs = with pkgs; [ cjson cmake ];
          shellHook = ''
            cmake -B build -DCMAKE_EXPORT_COMPILE_COMMANDS=ON
            ln -sf build/compile_commands.json .
          '';
        };
      }
  ))
  ;
}

 
