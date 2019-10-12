# Test file for Lab4_SMsDigitalDoorLock
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

# Add tests below

test "Current state: Start\nState to transition to: PRESSPA0\nPORTC => 0x08"
setPINA 0x01 #PA0
set state = Start
continue 5
expect state PRESSPA0
expectPORTC 0x08
checkResult

test "Curent state: Start\n State to transition to: PRESSPA1\nExpected PORTC => 0x06"
setPINA 0x02 #PA1
set state = Start
continue 5
expect state PRESSPA1
expectPORTC 0x06
checkResult 

test "Current state: PRESSPA0\n State to transition to: PRESSPA1\nExpected PORTC => 0x06"
setPINA 0x02 #PA1
set state = PRESSPA0
continue 5
expect state PRESSPA1
expectPORTC 0x06
checkResult

test "Current state: Start\n State to transition to: RELEASEBOTH\nExpected PORTC => 0x00"
setPINA 0x03 #PA1 && PA0
set state = Start
#setPINA 0x03 #PA1 && PA0
continue 5
expect state RELEASEBOTH
expectPORTC 0x00
checkResult

test "Current state: PRESSPA1\n State to transition to: PRESSPA0\n Expected PORTC: 0x08"
setPINA 0x01
set state = PRESSPA1
continue 5
expect state PRESSPA0
expectPORTC 0x08
checkResult

test "Current state: RELEASEBOTH\n State to transition to: PRESSPA0\n Expected PORTC: 0x08"
setPINA 0x01
set state = RELEASEBOTH
continue 5
expect state PRESSPA0
expectPORTC 0x08
checkResult

# Report on how many tests passed/tests ran
set $passed=$tests-$failed
eval "shell echo Passed %d/%d tests.\n",$passed,$tests
echo ======================================================\n
