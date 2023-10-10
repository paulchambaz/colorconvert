# ColorConvert

ColorConvert is a program to convert and print various color formats: HEX, RGB, HSL, percentage and ratio.

## Usage

```sh
colorconvert [FORMAT_FLAG] [COLOR_VALUE]
```

### Format flags:

- `--rgb`: Specify color in RGB format
- `--hex`: Specify color in HEX format
- `--hsl`: Specify color in HSL format
- `--percent`: Specify color in percentage format
- `--ratio`: Specify color in ratio format

### Example output:

```
$ colorconvert --rgb '255,255,255' --hex '#ffffff' --hsl '0,0,100' --percent '100,100,100' --ratio '1.00,1.00,1.00'
rgb: 255,255,255 ; hex: #ffffff ; hsl: 0,0,100 ; percent: 100,100,100 ; ratio: 1.00,1.00,1.00
rgb: 255,255,255 ; hex: #ffffff ; hsl: 0,0,100 ; percent: 100,100,100 ; ratio: 1.00,1.00,1.00
rgb: 255,255,255 ; hex: #ffffff ; hsl: 0,0,100 ; percent: 100,100,100 ; ratio: 1.00,1.00,1.00
rgb: 255,255,255 ; hex: #ffffff ; hsl: 0,0,100 ; percent: 100,100,100 ; ratio: 1.00,1.00,1.00
rgb: 255,255,255 ; hex: #ffffff ; hsl: 0,0,100 ; percent: 100,100,100 ; ratio: 1.00,1.00,1.00
```

## Installation

```sh
git clone https://github.com/paulchambaz/colorconvert
cd colorconvert
make
sudo mv target/release/colorconvert /usr/bin/colorconvert
```

## Test

To test this program, do :

```sh
make test
```

## License

This project is licensed under the GPLv3 license.
For more information, read the LICENSE file.
