{ 
  description = "Traffic engineering";

  inputs.flake-utils.url = github:numtide/flake-utils;
  inputs.nur.url = github:pschuprikov/nur-packages;
  inputs.nixpkgs.url = github:NixOS/nixpkgs/nixos-21.11;

  outputs = { self, flake-utils, nur, nixpkgs }:
    flake-utils.lib.eachDefaultSystem (system: 
      let 
        pkgs = nixpkgs.legacyPackages.${system};
        nurpkgs = import nur { inherit pkgs; }; in {
      devShell = pkgs.mkShell {
        buildInputs = [ nurpkgs.qt5.omnetpp nurpkgs.qt5.omnetpp-inet ];
        shellHook = ''
          export INET_INCLUDE=${nurpkgs.qt5.omnetpp-inet}/include
          export INET_LDPATH=${nurpkgs.qt5.omnetpp-inet}/lib
        '';
      };
    });
}
