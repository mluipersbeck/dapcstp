# dapcstp
A solver for the prize-collecting Steiner tree and related problems.

> A Dual Ascent-Based Branch-and-Bound Framework for the Prize-Collecting Steiner Tree and Related Problems <br />
> Markus Leitner, Ivana Ljubić, Martin Luipersbeck, and Markus Sinnl <br />
> INFORMS Journal on Computing 201830:2 , 402-420 

The article can be downloaded [here](https://doi.org/10.1287/ijoc.2017.0788), the benchmark instances [here](https://www.dropbox.com/sh/vkvhcc7x5an5v5l/AACv6Ha_1R5LXXJd-Vzr9rKTa?dl=0).

## Dependencies

* [Boost C++ Libraries](http://www.boost.org/)

## Usage

* Build using make.
* Example usage (solve instance file 'instance.pcstp' of type 'prize-collecting Steiner tree problem' and write the solution to file 'instance.sol'):
```
./dapcstp instance.pcstp --type pcstp -o instance.sol
```
* Display all available options:
```
./dapcstp -h
```
* Supported problem types:
  * Prize-collecting Steiner tree problem (pcstp) - default
  * Maximum-weight connected subgraph problem (mwcs)
  * Node-weighted Steiner tree problem (nwstp)
  * Steiner tree problem (stp)

## License

This project is licensed under the AGPL - see the [LICENSE](LICENSE) file for details.
