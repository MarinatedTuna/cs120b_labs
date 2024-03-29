# Test file for Lab3_BitManip
# Partner name: Jenaro Vega

# commands.gdb provides the following functions for ease:
#   test "<message>"
#       Where <message> is the message to print. Must call this at the beginning of every test
#       Example: test "PINA: 0x00 => expect PORTC: 0x01"
#   checkResult
#       Verify if the test passed or failed. Prints "passed." or "failed." accordingly, 
#       Must call this at the end of every test.
#   expectPORTx <val>
#       With x as the port (A,B,C,D)
#       The value the port is epected to have. If not it will print the erroneous actual value
#   setPINx <val>
#       With x as the port or pin (A,B,C,D)
#       The value to set the pin to (can be decimal or hexidecimal
#       Example: setPINA 0x01
#   printPORTx f OR printPINx f 
#       With x as the port or pin (A,B,C,D)
#       With f as a format option which can be: [d] decimal, [x] hexadecmial (default), [t] binary 
#       Example: printPORTC d
#   printDDRx
#       With x as the DDR (A,B,C,D)
#       Example: printDDRB

echo ======================================================\n
echo Running all tests..."\n\n

# Example test:
test "PINA: 0x00, PINB: 0x00 => PORTC: 0"
# Set inputs
setPINA 0x00
setPINB 0x00
# Continue for several ticks
continue 2
# Set expect values
expectPORTC 0
# Check pass/fail

test "Fuel level is either 1 or 2 with low fuel sensor => PORTC: 96"
setPINA 0x01
setPINA 0x02
continue 5
expectPORTC 96
checkResult

test "Fuel level is either 3 or 4 with low fuel sensor => PORTC: 48"
setPINA 0x03
setPINA 0x04
continue 5
expectPORTC 112
checkResult

test "Fuel level is either 5 or 6 => PORTC: 56"
setPINA 0x05
setPINA 0x06
continue 5
expectPORTC 56
checkResult

test "Fuel level is either 7 or 8 or 9 => PORTC: 60"
setPINA 0x07
setPINA 0x08
setPINA 0x09
continue 5
expectPORTC 60
checkResult

test "Fuel level is either 10 or 11 or 12 => PORTC: 62"
setPINA 0x0A
setPINA 0x0B
setPINA 0x0C
continue 5
expectPORTC 62
checkResult

test "Fuel level is either 13 or 14 or 15 => PORTC: 63"
setPINA 0x0D
setPINA 0x0E
setPINA 0x0F
continue 5
expectPORTC 63
checkResult

test "Alert driver for not wearing seatbelt => PORTC: 0x80"
setPINA 0x60
continue 5
expectPORTC 0x80
checkResult

# Report on how many tests passed/tests ran
set $passed=$tests-$failed
eval "shell echo Passed %d/%d tests.\n",$passed,$tests
echo ======================================================\n
