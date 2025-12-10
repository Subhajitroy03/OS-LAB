INTRODUCTION TO SHELL SCRIPT

➡️ ARRAY

arr=( 1 2 3 4 )

1) TO GET A PARTICULAR INDEX IN ARRAY

echo ${arr[2]}
 
2) TO GET ALL VALUES
 
echo ${arr[*]}
 
3) TO GET LENGTH OF ARRAY

echo ${#arr[*]}

4)UPDATE THE ARRAY

arr+=( 5 6 7 )

5) KEY VALUE PAIRS IN ARRAY

declare -A myArray
myArray=( [name]=Paul [age]=20 )
echo "${myArray[name]}"

➡️ STRINGS
 
myVar="Hello World!"

length=${#myVar}

upper=${myVar^^}

lower=${myVar,,}

replace=${myVar/World/Buddy}  (var name, whom, to what)

slice=${myVar:6:11} (var name, start , how many characters)

➡️ USER INPUT

read <var_name>

read -p "Your name" NAME

➡️ ARITHMETIC OPERATIONS

1) Using let command

let a++
let a=5*10

EXAMPLE- 
a=10
b=5
let sum=a+b
let diff=a-b

echo "Sum: $sum"
echo "Difference: $diff"

2) USING DOUBLE BRACKETS

echo "Sum: $((a+b))"

or

a=10
b=5

(( sum = a + b ))
(( diff = a - b ))

echo "Sum: $sum"
echo "Difference: $diff"

➡️ CONDITIONAL STATEMENTS

1) BASIC IF-ELSE

if [ $marks -gt 40 ]     ### NOTE THE SPACE USED, BEFORE AND AFTER , '-gt' is '>' symbol  
then

	echo "You are PASS"

else

	echo "You are FAIL"

fi

2) CHART -

Equal -eq / ==
Greaterthanorequalto -ge
Lessthanorequalto -le
Not Equal -ne / !=
Greater Than -gt
Less Than -lt

3) MULTIPLE CONDITION WITH IF ELIF ELSE

if [ $marks -ge 80 ]
then
	echo "First Division""
elif [ $marks -ge 60 ]
then
	echo "Second Division"
else
	echo "Fail""
fi
