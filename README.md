## Checksum Utility

It's a console application for calculating and verifying file checksums with optional salt. This utility helps users ensure the integrity of files by generating and checking their checksums.

## Command Line Options

- **_--help_**: Display help information about the application.
- **_--version_**: Display the version of the application.
- **_--action_**: Specify the action to perform:
  - _calc_: Calculate the checksum for the specified file.
  - _check_: Verify the checksum against a previously calculated checksum.
- **_--file_**: Path to the file for which the checksum is to be calculated or verified.
- **_--checksum-file_**: Path to the file that contains the expected checksum (for the check action) or where to save the calculated checksum (for the calc action).
- **_--salt_**: Optional salt value to enhance checksum security.

## Examples

1. Display help information:
```
   checksum.exe --help
```
2. Display the version of the application:
```
  checksum.exe --version
```
3. Calculate the checksum for a file and save it to another file with a salt value:
```
  checksum.exe --action=calc --file=<path to a file> --checksum-file=<path to a checksum file> --salt=<string>
```
4. Verify a file's checksum against a previously saved checksum:
```
  checksum.exe --action=check --file=<path to a file> --checksum-file=<path to a checksum file> --salt=<string>
```

## Build
###### Windows (x86)

```
   cmake -G "Visual Studio 17 2022" -T v143 -A win32 -S . -B ./build
   cmake --build ./build --config Release --target ALL_BUILD -j 6 --
```

###### Windows (x64)

```
   cmake -G "Visual Studio 17 2022" -T v143 -A x64 -S . -B ./build
   cmake --build ./build --config Release --target ALL_BUILD -j 6 --
```
