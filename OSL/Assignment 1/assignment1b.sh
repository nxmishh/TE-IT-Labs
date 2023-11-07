
#!/bin/bash


# CREATE AN ADDRESS BOOK 
create_ab(){
	echo " "
	echo "--------------------------------------"
	echo " "
    read -p "Name of Address Book : " filename 
    touch $filename 
    printf "%-10s %-10s %-10s %-10s %-6s\n" "Name" "Ph No" "Area" "City" "pincode" >> $filename
}

# VIEW ADDRESS BOOK
 view_ab(){
 
	echo " "
	echo "--------------------------------------"
	echo " "
	read -p "Enter the name of the file : " name1
    cat $name1
}

# INSERT A RECORD 
 insert_ab(){
	echo " "
	echo "--------------------------------------"
	echo " "
	read -p "Enter the name of the file " name2
    
    read -p "Name : " name
    read -p "Phone No : " Phno
    read -p "Area : " area 
    read -p "City : " city
    read -p "Pincode : " pc
    
	printf "%-10s %-10d %-10s %-10s %-6d\n" "$name" "$Phno" "$area" "$city" "$pc" >> $name2
}

# SEARCH A RECORD
search_ab(){
    echo " "
    echo "-----------------------------------------"
    echo " "
    read -p "Enter the name of the file in which you want to search the record : " name2

    while [ true ]
    do 
    echo "Enter the criteria for search " 
    read -p " name(1)/ phno(2) / exit (3) : " chh
        if [ $chh -eq 1 ] ; then 
            read -p "Enter the name " nm
            
            if  grep -q $nm $name2   ; then 
            echo " Record found "
            grep $nm $name2

            else 
            echo " Record Not found "

            fi

        elif [ $chh -eq 2 ] ; then 
            read -p "Enter the phone no." phno2
            if  grep -q $phno2 $name2   ; then 
            echo " Record found "
            grep $phno2 $name2
            else 
            echo " Record Not found "
            fi

        elif [ $chh -eq 2 ] ; then 
            exit

        else 
            read -p "Enter the correct choice : " chh
        fi
    done
}


# DELETE A RECORD
 delete_ab(){
	echo " "
	echo "--------------------------------------"
	echo " "
	read -p "Enter the name of the file : " name4
	echo "Which record do you want to delete :"
	echo "Enter exact Phone no of record : "
	read phn

	echo "The following record will be deleted: "
	grep $phn $name4

	read -p "To proceed (y/n) :" ch

	if [[ $ch == "y" || $ch == "Y" ]]
	then 
	sed -i "/$phn/d" $name4	
	else
	exit
	fi
}

# MODIFY A RECORD
 modify_ab(){
	echo " "
	echo "--------------------------------------"
	echo " "
	read -p "Enter the name of the file : " name5
	echo "Modify Record "
	read -p "Enter exact Phone no of record that you want to modify : " ppn

	echo "The following record will be modified : "
	grep $ppn $name5
	
	read -p "Enter the old credential that you want to modify ( eg. name, phone no. etc ) :" oldword 
	echo
	read -p "Enter the new credential with which you want to replace :" newword

	sed -i "/$ppn/s/$oldword/$newword/g" $name5
}

code

# MAIN

while [ true ]
do 


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


read -p "Enter the choice " chh


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
