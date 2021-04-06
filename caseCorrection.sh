nano f2
echo "Enter a word"
read var
 
echo $var | tr '[a-z]' '[A-Z]'

echo "Enter a word for lowercase"
read var2
 
echo $var2 | tr '[A-Z]' '[a-z]'

bash f2
