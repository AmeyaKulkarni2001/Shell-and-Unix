nano f1
echo "1 addition 2 Subtraction 3 multiplication 4 division"
read var
echo "Enter first number"
read num1
echo "Enter second number"
read num2
 
case $var in
1) sum= expr $num1 + $num2
   echo 'The Sum is' $sum
   ;;
2) sub= expr $num1 - $num2
   echo The Subtraction is' $sub
   ;;
3) mul= expr $num1 \* $num2
   echo 'The Multiplication is' $mul
   ;;
4) div= expr "scale=1 ; $num1 / $num2" | bc
   echo 'The division is' $div
   ;;
*) echo "Sorry, the option number should be less than Four"
   ;;
esac

bash f1
