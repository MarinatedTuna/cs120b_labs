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
checkResult

# Add tests below

test "PINA has one 1's => PORTC: 1"
setPINA 0x01
continue 5
expectPORTC 1
checkResult

test "PINA has two 1's => PORTC: 2"
setPINA 0x02
continue 5
expectPORTC 2
checkResult

test "PINA has three 1's => PORTC: 3"
setPINA 0x03
continue 5
expectPORTC 3
checkResult

test "PINA has four 1's => PORTC: 4"
setPINA 0x04
continue 5
expectPORTC 4
checkResult

test "PINA has five 1's => PORTC: 5"
setPINA 0x05
continue 5
expectPORTC 5
checkResult

test "PINA has six 1's => PORTC: 6"
setPINA 0x06
continue 5
expectPORTC 6
checkResult

test "PINA has seven 1's => PORTC: 7"
setPINA 0x07
continue 5
expectPORTC 7
checkResult

test "PINA has eight 1's => PORTC: 8"
setPINA 0x08
continue 5
expectPORTC 8
checkResult

# Report on how many tests passed/tests ran
set $passed=$tests-$failed
eval "shell echo Passed %d/%d tests.\n",$passed,$tests
echo ======================================================\n
