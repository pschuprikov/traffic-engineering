{ 
  description = "Traffic engineering";

  inputs.flake-utils.url = github:numtide/flake-utils;
  inputs.nur.url = github:pschuprikov/nur-packages;
  inputs.nixpkgs.url = github:NixOS/nixpkgs/nixos-25.05;

  outputs = { self, flake-utils, nur, nixpkgs }:
    flake-utils.lib.eachDefaultSystem (system: 
      let 
        pkgs = nixpkgs.legacyPackages.${system};
        nurpkgs = nur.packages.${system}; in {
      devShell = pkgs.mkShell {
        buildInputs = [ nurpkgs.omnetpp_6_0 nurpkgs.omnetpp-inet_4_3_9 ];
        shellHook = ''
          export INET_INCLUDE=${nurpkgs.omnetpp-inet_4_3_9}/include
          export INET_LDPATH=${nurpkgs.omnetpp-inet_4_3_9}/lib
        '';
      };
    });
}
