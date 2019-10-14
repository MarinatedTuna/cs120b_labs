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

test "Current state: Start\nState to transition to: PRESS\nExpected PORTC => 0"
setPINA 0x04 #PA2
set state = Start
continue 5
expect state PRESS
expectPORTC 0
checkResult

test "Current state: PRESS\nState to transition to: RELEASE\nExpected PORTC => 0"
set state = PRESS
setPINA 0x00 #~PA2
continue 5
expect state RELEASE
expectPORTC 0
checkResult

test "Current state: RELEASE\nState to transition to: PRESS2\nExpected PORTC => 1"
setPINA 0x02
set state = RELEASE
continue 5
expect state PRESS2
expectPORTC 1
checkResult 

test "Current state: PRESS2\nState to transition to: Start\nExpected PORTC => 0"setPINA 0x80
set state = PRESS2
continue 5
expect state Start
expectPORTC 0
checkResult

test "Testing broken sequence from PRESS\nState to transition to: Start\nExpected PORTC => 0"
setPINA 0x01
set state = PRESS
continue 5
expect state Start
expectPORTC 0
checkResult

test "Testing broken sequence from RELEASE\nState to transition to: Start\nExpected PORTC => 0"
setPINA 0x06
set state = RELEASE
continue 5
expect state Start
expectPORTC 0
checkResult

test "Testing trying to lock while not in the house what from PRESS2\nState to transition to: PRESS2\nExpected PORTC => 1"
setPINA 0x09
set state = PRESS2
continue 5
expect state PRESS2
expectPORTC 1
checkResult 

# Report on how many tests passed/tests ran
set $passed=$tests-$failed
eval "shell echo Passed %d/%d tests.\n",$passed,$tests
echo ======================================================\n
