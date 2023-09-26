
#!/bin/bash


# CREATE AN ADDRESS BOOK 
create_ab(){
	echo " "
	echo "--------------------------------------"
	echo " "
    read -p "Name of Address Book : " filename 
    touch $filename 
    printf "%-1s %-10s %-5s %-10s %-6s\n" "name" "Phno" "area" "city" "pincode" >> $filename
}

# VIEW ADDRESS BOOK
 view_ab(){
	echo " "
	echo "--------------------------------------"
	echo " "
    cat $filename
}

# INSERT A RECORD 
 insert_ab(){
	echo " "
	echo "--------------------------------------"
	echo " "
    
    read -p "Name : " name
    read -p "Phone No : " Phno
    read -p "Area : " area 
    read -p "City : " city
    read -p "Pincode : " pc
    
    printf "%-1s %-10s %-5s %-10s %-6s\n" "$name" "$Phno" "$area" "$city" "$pincode" >> "$filename"
}

# SEARCH A RECORD
 search_ab(){
	echo " "
	echo "--------------------------------------"
	echo " "

	echo "Which criteria do you want to search"

	read -p " Name(1) or Phno(0) : " choice

	if [ $choice -eq 1 ]
	then 
	read -p "Enter the name :" nm
	grep $nm $filename

	elif [ $choice -eq 0 ]
	then 
	read -p "Enter the Phone no :" pn

	echo "Record(s) Found :"

	grep $pn $filename

	elif [ $choice -eq 2 ]
	then 
	exit 

	else 
	echo "Enter valid criteria to search"

	read -p "Name(1) or Phno(0) :" choice

	fi
}

# DELETE A RECORD
 delete_ab(){
	echo " "
	echo "--------------------------------------"
	echo " "
	echo "Which record do you want to delete :"
	echo "Enter exact Phone no of record : "
	read phn



	echo "The following record will be deleted: "
	grep $phn $filename



	read -p "To proceed (y/n) :" ch

	if [[ ch -eq 121 ]]
	then 
	sed '/$phn/d' ./$filename 
	else
	exit
	fi
}

# MODIFY A RECORD
 modify_ab(){
	echo " "
	echo "--------------------------------------"
	echo " "
	echo "Modify Record "
	read -p "Enter exact Phone no of record that you want to modify : " ppn

	echo "The following record will be modified : "
	grep $ppn $filename

	prevrec=$(grep $ppn $filename) 



	echo "Enter the record with which you want to replace :" 
	echo "Name" "Phone No" "Area" "City" "Pin Code"
	read newrec



	sed 's/$prevrec/$newrec/g' $filename
}

code

# MAIN
echo " "
echo "--------------------------------------"
echo " "

echo " Address Book "

echo " 1 . Create New Address Book "
echo " 2 . View Address Book "
echo " 3 . Insert a record in Address Book "
echo " 4 . Search a record in Address Book "
echo " 5 . Delete a record in Address Book "
echo " 6 . Modidy a record in Address Book "
echo " 7 . Exit "

echo ""
echo ""

while [ true ]
do 

read -p "Enter the choice " chh

echo " "
echo "--------------------------------------"
echo " "


	case $chh in
	  1)
	    create_ab
	    ;;
	 2)
	   view_ab
	   ;;
	 3)
	   	insert_ab
	   ;;
	 4)
		search_ab
	    ;;
	 5)
		delete_ab
	   ;;
	 6)
		modify_ab
	    ;;
	 7)
	   exit
	   ;;
	esac

done
