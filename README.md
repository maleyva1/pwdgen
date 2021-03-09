# pwdgen

Simple CLI password generator for Linux. Can generate
alphanmeric, digit-only, symbol-only, or 
alphanumeric-with-symbols passwords of variable length.

## Usage

`pwdgen [a|s|d|asd] LENGTH`

### Example

`pwdgen asd 15`

## Building

Feel free to use the include `build.sh` script or 
follow the commands below

```bash
cmake -B build -DCMAKE_BUILD_TYPE=$BUILD_TYPE
cd build && make -J 4
```