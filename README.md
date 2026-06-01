# 3s - Generic Typed Data Structures Library

C library with the implementation of some data structures.
The intent is to have data structures that can simultaneously hold more than one specific type of data.

## How to test the examples?

Run the following command to compile the examples:

```sh
make examples
```

Then run the numbered tests, for example to run the first test, run:

```sh
./example01
```

## How to run unit tests?

First make sure you've also cloned the submodule used for tests, [tinytest](https://github.com/anaximeno/tinytest) inside the root folder of this project, you can do it with the command:

```sh
git submodule update --init
```

If everything went ok you can then execute the tests with:

```sh
make test
```