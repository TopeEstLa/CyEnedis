# CyEnedis 🗿🗿

Pre-Ing-2 S1 IT project <br>
Subject CyWire [subject.pdf](subject.pdf) <br>
Project report [report.pdf](RapportProjetInformatique.pdf) <br>

## Compilation

```bash
./c-wire.sh -c
```

## Execution

### Arguments
- input_file: path to the input file
- station_type: type of station (hvb, hva, lv)
- consumer_type: type of consumer (indiv, comp, all)
- power_plant_id: id of the power plant (optional)

⚠️ some case are not allowed (hvb all/indiv) & (hva all/indiv)

```bash
./c-wire.sh input/[input_file] [station_type(hvb, hva, lv)] [consumer_type(indiv, comp, all)] (power_plant_id)
```
### Example

```bash
./c-wire.sh input/test-data.csv lv all
```
## Dependencies
- pthread

## Env variables
- RUNNING_BENCHMARK: Set to 1 to run benchmarks

## Shell script exit code

- 0: Success
- 20: Error when creating directory
- 21: Error when compiling C program
- 22: Error with given arguments

if c program exit code is not 0, shell script exit code will be the c program exit code

## C program exit code

- 0: Success
- 2: Error when parsing arguments
- 3: Invalid argument
- 4: Error when reading file and building AVL tree
- 5: Error while using data from AVL tree
- 6: Error while writing csv file
- 7: Error while writing minmax csv file