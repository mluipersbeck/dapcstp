# dapcstp
A solver for the prize-collecting Steiner tree and related problems.

> A dual-ascent-based branch-and-bound framework for the prize-collecting Steiner tree and related problems <br />
> M. Leitner, I. Ljubić, M. Luipersbeck, M. Sinnl

The technical report can be downloaded [here](http://www.optimization-online.org/DB_FILE/2016/06/5509.pdf), the benchmark instances [here](https://www.dropbox.com/sh/vkvhcc7x5an5v5l/AACv6Ha_1R5LXXJd-Vzr9rKTa?dl=0).

## Dependencies

* [Boost C++ Libraries](http://www.boost.org/)

## Usage

* Build using make.
* Example usage (Solve instance file 'instance.pcstp' o and writes the solution to file 'instance.sol'):
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
