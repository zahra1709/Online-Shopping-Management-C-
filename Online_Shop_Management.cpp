#include <iostream>
#include <regex>
#include <conio.h>
#include <fstream>
#include <sstream>
#include <string>
#include <sys/stat.h>
#include <sys/types.h>
#include <direct.h>
#include <iomanip>
#include <cmath>

using namespace std;



string generateId(string filename)
{
	// Open the file for reading
	ifstream file(filename);
	// Read the last line of the file
	string lastLine;
	string line;
	int lineCount = 0;

	while (getline(file, line))
	{
		lastLine = line;
		lineCount++;
	}
	if (lineCount != 1)
	{
		// Extract the ID from the last line
		string id;
		stringstream lineStream(lastLine);
		getline(lineStream, id, '\t');

		// Convert the ID to integer and add 1
		int newId = stoi(id) + 1;

		// Convert the new ID back to string
		stringstream newIdStream;
		newIdStream << setw(id.length()) << setfill('0') << newId;
		string newIdString = newIdStream.str();

		return newIdString;
	}
	else
	{
		return "0001";
	}

}

class Category {
	public: 
	string categoryId;
	string name;
	
	public:
	Category(){
			
		}
		
	Category (string categoryId){
			this->categoryId = categoryId;
			ifstream categoryFile ("files/Categories.txt");
			
			string line, name;
			getline (categoryFile, line); //skip the header row
			
			if (categoryFile.is_open()){
				while (getline(categoryFile, line))
				{
					stringstream lineStream(line);
					
					getline(lineStream, categoryId, '\t');
					getline(lineStream, name, '\t');
					
					if (categoryId == this->categoryId)
					{
						this->name = name;
						categoryFile.close();
						return;
					}
				}
				categoryFile.close();
			}
			return;
		} 
		
	Category(string categoryId, string name)
		{ 
		    this->categoryId = categoryId;
		    this->name = name;
			
		}
		
	bool setName() {
			
			while(true) {
				
				cout << "\nEnter a category name: ";
				string newName;
				getline(cin, newName);
				
				newName.erase(std::remove(newName.begin(), newName.end(), '\t'), newName.end());
				
				if (newName.empty())
				{
					cout << "\nThe name cannot be empty! Please enter a valid name." << endl;
					continue;
				}
				
				ifstream categoryFile("files/Categories.txt");
				
				string line, categoryId, name;
				getline (categoryFile, line);
				this->name = newName;
				if (categoryFile.is_open())
				{
					while (getline(categoryFile, line))
					{
						stringstream lineStream(line);
						
						getline(lineStream, categoryId, '\t');
					getline(lineStream, name, '\t');

					for (int i = 0; i < name.length(); i++)
						name[i] = tolower(name[i]);

					for (int i = 0; i < newName.length(); i++)
						newName[i] = tolower(newName[i]);

					if (name == newName && categoryId != this->categoryId)
					{
						cout << "\nThis category already exists." << endl;
						categoryFile.close();
						return false;
					}
				}
				categoryFile.close();
			}
			return true;
		}

	}
	
	
	int countCategory() {
		
		string line;
		ifstream categoryFile("files/Categories.txt");
		getline(categoryFile, line);

		int categoryCount = 0;

		if (categoryFile.is_open())
		{
			// Get the number of managers
			while (getline(categoryFile, line))
			{
				categoryCount++;
			}
			categoryFile.close();
		}

		return categoryCount;
	}
	
	void showAllCategories() {
		
		string line;
		ifstream categoryFile("files/Categories.txt");
		
		if (categoryFile.is_open()) {
			
			cout << endl;
			
			int categoryCount = 0;
			
			getline(categoryFile, line);
			
		    cout << ".~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~." << endl;
			cout << "|           CATEGORIES           |" << endl;
			cout << ".~~~~~~~~~~~~~.~~~~~~~~~~~~~~~~~~." << endl;
			cout << "| Category ID |   Category Name  |" << endl;
			cout << ".~~~~~~~~~~~~~.~~~~~~~~~~~~~~~~~~." << endl;
	    while (getline(categoryFile, line))
			{
				stringstream lineStream(line);
				string categoryId, name;
				// Read each cell (column) from the line
				getline(lineStream, categoryId, '\t');
				getline(lineStream, name, '\t');
				
				cout << "|    " << categoryId << "     | " << setw(16)  << left << name << " |" << endl;
				categoryCount++;
			
		}
		cout << ".~~~~~~~~~~~~~.~~~~~~~~~~~~~~~~~~." << endl;
		cout << endl << "\nTotal no. categories in store: " << categoryCount << endl << endl;
		categoryFile.close();
	}
}
	
	void chooseCategory()
	{
		string line, choice;
		ifstream categoryFile("files/Categories.txt");

		while (true)
		{

			cout << "Enter Category ID: ";
			cin >> choice;
			choice.erase(std::remove(choice.begin(), choice.end(), '\t'), choice.end());
			
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');

			if (categoryFile.is_open())
			{

				getline(categoryFile, line); 

				while (getline(categoryFile, line))
				{
					stringstream lineStream(line);
					string categoryId;

					getline(lineStream, categoryId, '\t');

					if (choice == categoryId)
					{
						string name;
						this->categoryId = categoryId;
						getline(lineStream, this->name, '\t');
						categoryFile.close();

						return;
					}
				}
				categoryFile.clear(); // Clear any existing flags
				categoryFile.seekg(0, ios::beg); // Move cursor to the beginning of the file
				cout << "The Category ID is inavlid. Please enter a valid ID." << endl;
			}
		}
	}
	
	bool addCategory(){
		
		this->categoryId = generateId("files/Categories.txt");
		ofstream userFile("files/Categories.txt", ios::app);
		if (userFile.is_open()) {
			
			userFile << this->categoryId << "\t" << this->name << endl;
			userFile.close();
			return true;
		}
	
		return false;
	}
	
	void editCategory() 
	{
		if (this->categoryId == "0000"){
			
			cout << "\nThis ID cannot be edited." << endl;
			return;
		}
		
			cout << ".~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~." << endl;
			cout << "|              CATEGORY               |" << endl;
			cout << ".~~~~~~~~~~~~~~~~~~.~~~~~~~~~~~~~~~~~~." << endl;
			cout << "| 1. Category ID   | " << setw(16) << this->categoryId << " |" << endl;
			cout << "| 2. Category Name | " << setw(16) << this->name << " |" << endl;
			cout << ".~~~~~~~~~~~~~~~~~~.~~~~~~~~~~~~~~~~~~." << endl;
			
			cout << "\nCategory ID is not editable. You can only edit the name." << endl;
			setName();
			
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');

			

	}
	
	void updateCategory() {
		
		if (this->categoryId == "0000"){
			return;
		}
		
		ifstream categoryFile("files/Categories.txt");
		if (!categoryFile.is_open()) {
			cout << "Could not update!" << endl;
			return;
		}
		
		ofstream tempCategoryFile("files/tempCategories.txt");	
	
		if (!tempCategoryFile.is_open())
		{
			categoryFile.close();
			cout << "Could not update!" << endl;
			return;
		}

		string line;
		while (getline(categoryFile, line))
		{
			stringstream lineStream(line);
			string categoryId, name;

			getline(lineStream, categoryId, '\t');
			getline(lineStream, name, '\t');

			
			if (categoryId == this->categoryId)
			{
				// If it matches, write the updated data to the temp file
				tempCategoryFile << this->categoryId << "\t" << this->name << endl;
			}
			else
			{
				// If it doesn't match, write the original data to the temp file
				tempCategoryFile << categoryId << "\t" << name << endl;
			}
		}

		categoryFile.close();
		tempCategoryFile.close();

		// Remove the original file
		if (remove("files/Categories.txt") != 0)
		{
			cout << "Could not update!" << endl;
			return;
		}

		if (rename("files/tempCategories.txt", "files/Categories.txt") != 0)
		{
			cout << "Could not update!." << endl;
			return;
		}

		cout << "\nCategory details have been updated!" << endl;
		return;
	}
	
	void deleteCategory() {
		
		if (this->categoryId == "0000")
		{
			cout << "\nYou cannot delete this category!" << endl;
			return;
		}
		
		ifstream categoryFile("files/Categories.txt");
		
			if (!categoryFile.is_open())
		{
			cout << "Delete failed." << endl;
			return;
		}

		// Create a temporary file for writing the updated data
		ofstream tempCategoryFile("files/tempCategories.txt");

		// check if file is open
		if (!tempCategoryFile.is_open())
		{
			categoryFile.close();
			cout << "Delete failed." << endl;
			return;
		}

		string line;
		while (getline(categoryFile, line))
		{
			stringstream lineStream(line);
			string categoryId, name;

			getline(lineStream, categoryId, '\t');
			getline(lineStream, name, '\t');

			if (categoryId != this->categoryId)
			{
				// If it doesn't match, write the original data to the temp file
				// Otherwise skip
				tempCategoryFile << categoryId << "\t" << name << endl;
			}

		}
		categoryFile.close();
		tempCategoryFile.close();

		// Remove the original file
		if (remove("files/Categories.txt") != 0)
		{
			cout << "Delete failed." << endl;
			return;
		}

		// Rename the temp file to the original file name
		if (rename("files/tempCategories.txt", "files/Categories.txt") != 0)
		{
			cout << "Delete failed." << endl;
			return;
		}

		//Update Category details in products file

		ifstream productFile("files/Products.txt");

		// check if file is open
		if (!productFile.is_open())
		{

			cout << "Update failed." << endl;
			return;
		}

		// Create a temporary file for writing the updated data
		ofstream tempProductFile("files/tempProducts.txt");

		// check if file is open
		if (!tempProductFile.is_open())
		{
			productFile.close();
			cout << "Update failed." << endl;
			return;
		}

		// Read the lines from the original file
		while (getline(productFile, line))
		{
			stringstream lineStream(line);
			string productId, name, categoryId, itemPrice, packagingPrice, qty, description;

			// Read each cell (column) from the line
			getline(lineStream, productId, '\t');
			getline(lineStream, name, '\t');
			getline(lineStream, categoryId, '\t');
			getline(lineStream, itemPrice, '\t');
			getline(lineStream, packagingPrice, '\t');
			getline(lineStream, qty, '\t');
			getline(lineStream, description, '\t');

			// Check if the categoryId from the file matches the categoryId of the current User object
			if (categoryId == this->categoryId)
			{
				// If it matches, write the updated data to the temp file
				tempProductFile << productId << "\t" << name << "\t" << "0000" << "\t" << itemPrice << "\t" << packagingPrice << "\t" << qty << "\t" << description << endl;
			}
			else
			{
				// If it doesn't match, write the original data to the temp file
				tempProductFile << productId << "\t" << name << "\t" << categoryId << "\t" 	<< itemPrice << "\t" << packagingPrice << "\t" << qty << "\t" << description << endl;
			}
		}

		// Close the original file and the temp file
		productFile.close();
		tempProductFile.close();

		// Remove the original file
		if (remove("files/Products.txt") != 0)
		{
			cout << "Update failed." << endl;
			return;
		}
		// Rename the temp file to the original file name
		if (rename("files/tempProducts.txt", "files/Products.txt") != 0)
		{
			cout << "Update failed." << endl;
			return;
		}

		cout << "The category has been deleted!" << endl;
		return;
	}
	
	void searchCategory(string search)
	{
		string line;
		ifstream categoryFile("files/Categories.txt");

		//converting search key to lower case
		for (int i = 0; i < search.length(); i++)
			search[i] = tolower(search[i]);


		if (categoryFile.is_open())
		{
			cout << endl;
			int categoryCount = 0;
			// Read the lines from file
			getline(categoryFile, line);
			cout << ".~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~." << endl;
			cout << "|           CATEGORIES           |" << endl;
			cout << ".~~~~~~~~~~~~~.~~~~~~~~~~~~~~~~~~." << endl;
			cout << "| Category ID |   Category Name  |" << endl;
			cout << ".~~~~~~~~~~~~~.~~~~~~~~~~~~~~~~~~." << endl;
			while (getline(categoryFile, line))
			{
				stringstream lineStream(line);
				string categoryId, name;
				// Read each cell (column) from the line
				getline(lineStream, categoryId, '\t');
				getline(lineStream, name, '\t');

				for (int i = 0; i < line.length(); i++)
					line[i] = tolower(line[i]);

				if (line.find(search) != string::npos or categoryId == "Category ID")
				{
					cout << "|    " << categoryId << "     | " << setw(16)  << left << name << " |" << endl;
				categoryCount++;
			
		}
		    cout << ".~~~~~~~~~~~~~.~~~~~~~~~~~~~~~~~~." << endl;
			cout << endl << "\nTotal no. of categories: " << categoryCount << endl << endl;
			categoryFile.close();
		}
	}
}
												
};


class Product
{
public:
	string productId;
	string categoryId;
	string name;
	int qty;
	float itemPrice;
	float packagingPrice;
	string details;


public:
	Product()
	{
		
	}

	Product(string productId)
	{
		this->productId = productId;

		string line;
		ifstream productFile("files/Products.txt");

		if (productFile.is_open())
		{
			getline(productFile, line); //Skip the header row

			while (getline(productFile, line))
			{
				stringstream lineStream(line);
				string productId;

				getline(lineStream, productId, '\t');

				if (this->productId == productId)
				{
					string name, categoryId, itemPrice, packagingPrice, qty, details;
					// Read each cell (column) from the line
					this->productId = productId;
					getline(lineStream, this->name, '\t');
					getline(lineStream, this->categoryId, '\t');
					getline(lineStream, itemPrice, '\t');
					getline(lineStream, packagingPrice, '\t');
					getline(lineStream, qty, '\t');
					getline(lineStream, this->details, '\t');

					this->itemPrice = stof(itemPrice); //string to float
					this->packagingPrice = stof(packagingPrice);
					this->qty = stoi(qty); //string to integer
					
					productFile.close();

					return;
				}
			}
			this->qty = 0;
			this->name = ""; //qty is zero and name is empty initially
		}
	}

	void setCategory()
	{
		Category category;  //composition

		category.showAllCategories();
		category.chooseCategory();

		this->categoryId = category.categoryId;

	}

	void setName()
	{
		// Keep asking for input until the user enters a non-empty name
		while (true)
		{
			cout << "\nEnter Product Name: ";

			getline(cin, this->name);
			this->name.erase(std::remove(this->name.begin(), this->name.end(), '\t'), this->name.end());
			if (!this->name.empty())
			{
				// Name is not empty, exit loop
				break;
			}
			cout << "\nProduct Name cannot be empty. Please try again." << endl;
		}
	}

	void setItemPrice()
	{
		while (true)
		{
			cout << "\nEnter price of product (in RM): ";

			string priceInput;
			getline(cin, priceInput);
			priceInput.erase(std::remove(priceInput.begin(), priceInput.end(), '\t'), priceInput.end());
			try
			{
				this->itemPrice = stof(priceInput);
				if (this->itemPrice > 0)
				{
					this->itemPrice = round(this->itemPrice * 100) / 100; // Round to 2 decimal places
					break;
				}
			}
			catch (invalid_argument&)
			{
				// Do nothing, just continue the loop
			}

			cout << "\nPlease enter a valid amount!" << endl;
		}
	}

	void setPackagingPrice()
	{
		while (true)
		{
			cout << "\nEnter price of packaging (in RM): ";

			string priceInput;
			getline(cin, priceInput);
			priceInput.erase(std::remove(priceInput.begin(), priceInput.end(), '\t'), priceInput.end());
			try
			{
				this->packagingPrice = stof(priceInput);
				if (this->packagingPrice >= 0)
				{
					this->packagingPrice = round(this->packagingPrice * 100) / 100; // Round to 2 decimal places
					break;
				}
			}
			catch (invalid_argument&)
			{
				// Do nothing, just continue the loop
			}

			cout << "\nEnter a valid amount please." << endl;
		}
	}


	void setQty()
{
	while (true)
	{
		cout << "\nEnter quantity in inventory: ";

		string qtyInv;
		getline(cin, qtyInv);
		qtyInv.erase(std::remove(qtyInv.begin(), qtyInv.end(), '\t'), qtyInv.end());
		try
		{
			int qty = stoi(qtyInv);

			if (qty >= 0 && qty <= 500) // Check if the quantity is non-negative and does not exceed 500.
			{
				this->qty = qty;
				break;
			}
			else
			{
				cout << "\nInvalid quantity. Please enter a non-negative value not exceeding 500." << endl;
			}
		}
		catch (invalid_argument&)
		{
			// Do nothing, just continue the loop
		}
        cout << "\nInvalid quantity. Please try again." << endl;
	}
}

	void setDetails()
	{
		// Keep asking for input until the user enters a non-empty name
		while (true)
		{
			cout << "\nProduct details: ";
			getline(cin, this->details);
			this->details.erase(std::remove(this->details.begin(), this->details.end(), '\t'), this->details.end());
			if (!this->details.empty())
			{
				break;
			}
			cout << "\nPlease add some details about the product." << endl;
		}
	}

	bool addProduct()
	{
		this->productId = generateId("files/Products.txt");

		//Write into file
		ofstream productFile("files/Products.txt", ios::app);
		if (productFile.is_open())
		{

			productFile << this->productId << "\t" << this->name << "\t" << this->categoryId << "\t"
				<< fixed << setprecision(2) << this->itemPrice << "\t"
				<< fixed << setprecision(2) << this->packagingPrice << "\t"
				<< this->qty << "\t" << this->details << endl;
			productFile.close();
			return true;
		}
		//If everything goes well return true
		return false;
	}

	int countProduct()
	{
		string line;
		ifstream productFile("files/Products.txt");

		//Read the first line
		getline(productFile, line);

		int productCount = 0;

		if (productFile.is_open())
		{
			// Get the number of managers
			while (getline(productFile, line))
			{
				productCount++;
			}
			productFile.close();
		}

		return productCount;
	}

	void showAllProducts()
	{
		string line;
		ifstream productFile("files/Products.txt");


		if (productFile.is_open())
		{
			getline(productFile, line); // Skip the header row
			

			cout << ".~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~." << endl;
			cout << "|                                                                               PRODUCTS                                                                             |" << endl;
			cout << ".~~~~~~~~~~~~.~~~~~~~~~~~~~~~~.~~~~~~~~~~~~~.~~~~~~~~~~~~~~~~~~.~~~~~~~~~~~~~~.~~~~~~~~~~~~~~~~~.~~~~~~~~~~~~~~~.~~~~~~~~~~.~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~." << endl;
			cout << "| Product ID | Product Name   | Category ID | Category Name    |  Item Price  | Packaging Price |  Total Price  | Quantity |                Details                  |" << endl;
			cout << ".~~~~~~~~~~~~.~~~~~~~~~~~~~~~~.~~~~~~~~~~~~~.~~~~~~~~~~~~~~~~~~.~~~~~~~~~~~~~~.~~~~~~~~~~~~~~~~~.~~~~~~~~~~~~~~~.~~~~~~~~~~.~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~." << endl;
			int productCount = 0;
			// Read the lines from file
			while (getline(productFile, line))
			{
				stringstream lineStream(line);
				string productId, name, categoryId, itemPrice, packagingPrice, qty, details;
				// Read each cell (column) from the line
				getline(lineStream, productId, '\t');
				getline(lineStream, name, '\t');
				getline(lineStream, categoryId, '\t');
				getline(lineStream, itemPrice, '\t');
				getline(lineStream, packagingPrice, '\t');
				getline(lineStream, qty, '\t');
				getline(lineStream, details, '\t');

				Category category(categoryId);


				cout << "|    " << productId << "    |" << setw(16) << left << name
					<< "|    " << categoryId << "     | " << setw(16) << left<< category.name
					<< " | RM " << setw(10) << left<< itemPrice
					<< "|  RM " << setw(9) << left<< packagingPrice
					<< "   | RM " << setw(11)  << fixed << left<<  setprecision(2) << stof(itemPrice) + stof(packagingPrice)
					<< "| " << setw(5) << qty << "    | " << setw(39) << left << details << " |" << endl;
				productCount++;
			}

			cout << ".~~~~~~~~~~~~.~~~~~~~~~~~~~~~~.~~~~~~~~~~~~~.~~~~~~~~~~~~~~~~~~.~~~~~~~~~~~~~~.~~~~~~~~~~~~~~~~~.~~~~~~~~~~~~~~~.~~~~~~~~~~.~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~." << endl;
			cout << endl << "\nTotal no. of products in store: " << productCount << endl << endl;
			productFile.close();
		}
	}

	void showProductsByCategory()
	{
		string line;
		ifstream productFile("files/Products.txt");


		if (productFile.is_open())
		{
			getline(productFile, line); // Skip the header row
			

			cout << ".~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~." << endl;
			cout << "|                                                                               PRODUCTS                                                                             |" << endl;
			cout << ".~~~~~~~~~~~~.~~~~~~~~~~~~~~~~.~~~~~~~~~~~~~.~~~~~~~~~~~~~~~~~~.~~~~~~~~~~~~~~.~~~~~~~~~~~~~~~~~.~~~~~~~~~~~~~~~.~~~~~~~~~~.~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~." << endl;
			cout << "| Product ID | Product Name   | Category ID | Category Name    |  Item Price  | Packaging Price |  Total Price  | Quantity |                Details                  |" << endl;
			cout << ".~~~~~~~~~~~~.~~~~~~~~~~~~~~~~.~~~~~~~~~~~~~.~~~~~~~~~~~~~~~~~~.~~~~~~~~~~~~~~.~~~~~~~~~~~~~~~~~.~~~~~~~~~~~~~~~.~~~~~~~~~~.~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~." << endl;
			int productCount = 0;
			// Read the lines from file
			while (getline(productFile, line))
			{
				stringstream lineStream(line);
				string productId, name, categoryId, itemPrice, packagingPrice, qty, details;
				// Read each cell (column) from the line
				getline(lineStream, productId, '\t');
				getline(lineStream, name, '\t');
				getline(lineStream, categoryId, '\t');
				getline(lineStream, itemPrice, '\t');
				getline(lineStream, packagingPrice, '\t');
				getline(lineStream, qty, '\t');
				getline(lineStream, details, '\t');

				Category category(categoryId);

				if (this->categoryId == categoryId)
				{
					cout << "|    " << productId << "    |" << setw(16) << name
						<< "|    " << categoryId << "     | " << setw(16) << category.name
						<< " | RM " << setw(10) << itemPrice
						<< "|  RM " << setw(9) << packagingPrice
						<< "   | RM " << setw(11) << fixed << setprecision(2) << stof(itemPrice) + stof(packagingPrice)
						<< "| " << setw(5) << qty << "    | " << setw(39) << details << " |" << endl;
					productCount++;
				}
			}

			cout << ".~~~~~~~~~~~~.~~~~~~~~~~~~~~~~.~~~~~~~~~~~~~.~~~~~~~~~~~~~~~~~~.~~~~~~~~~~~~~~.~~~~~~~~~~~~~~~~~.~~~~~~~~~~~~~~~.~~~~~~~~~~.~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~." << endl;
			cout << endl << "\nTotal no. of products in store: " << productCount << endl << endl;
			productFile.close();
		}
	}

	void searchProduct(string search)
	{
		string line;
		ifstream productFile("files/Products.txt");

		//converting search key to lower case
		for (int i = 0; i < search.length(); i++)
			search[i] = tolower(search[i]);
		if (productFile.is_open())
		{
			getline(productFile, line); // Skip the header row
			

			cout << ".~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~." << endl;
			cout << "|                                                                               PRODUCTS                                                                             |" << endl;
			cout << ".~~~~~~~~~~~~.~~~~~~~~~~~~~~~~.~~~~~~~~~~~~~.~~~~~~~~~~~~~~~~~~.~~~~~~~~~~~~~~.~~~~~~~~~~~~~~~~~.~~~~~~~~~~~~~~~.~~~~~~~~~~.~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~." << endl;
			cout << "| Product ID | Product Name   | Category ID | Category Name    |  Item Price  | Packaging Price |  Total Price  | Quantity |                Details                  |" << endl;
			cout << ".~~~~~~~~~~~~.~~~~~~~~~~~~~~~~.~~~~~~~~~~~~~.~~~~~~~~~~~~~~~~~~.~~~~~~~~~~~~~~.~~~~~~~~~~~~~~~~~.~~~~~~~~~~~~~~~.~~~~~~~~~~.~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~." << endl;

			int productCount = 0;
			// Read the lines from file
			while (getline(productFile, line))
			{
				stringstream lineStream(line);
				string productId, name, categoryId, itemPrice, packagingPrice, qty, details;
				// Read each cell (column) from the line
				getline(lineStream, productId, '\t');
				getline(lineStream, name, '\t');
				getline(lineStream, categoryId, '\t');
				getline(lineStream, itemPrice, '\t');
				getline(lineStream, packagingPrice, '\t');
				getline(lineStream, qty, '\t');
				getline(lineStream, details, '\t');

				Category category(categoryId);

				for (int i = 0; i < line.length(); i++)
					line[i] = tolower(line[i]);

				if (line.find(search) != string::npos)
				{
					
					cout << "|    " << productId << "    |" << setw(16) << name
						<< "|    " << categoryId << "     | " << setw(16) << category.name
						<< " | RM " << setw(10) << itemPrice
						<< "|  RM " << setw(9) << packagingPrice
						<< "   | RM " << setw(11) << fixed << setprecision(2) << stof(itemPrice) + stof(packagingPrice)
						<< "| " << setw(5) << qty << "    | " << setw(39) << details << " |" << endl;

					productCount++;
				}



			}
			cout << ".~~~~~~~~~~~~.~~~~~~~~~~~~~~~~.~~~~~~~~~~~~~.~~~~~~~~~~~~~~~~~~.~~~~~~~~~~~~~~.~~~~~~~~~~~~~~~~~.~~~~~~~~~~~~~~~.~~~~~~~~~~.~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~." << endl;
			cout << endl << "\nTotal products that match your search: " << productCount << endl << endl;
			productFile.close();
		}
	}

	void chooseProduct()
	{
		string line, chosenId;
		ifstream productFile("files/Products.txt");

		while (true)
		{

			cout << "\nEnter Product ID: ";
			cin >> chosenId;
			chosenId.erase(std::remove(chosenId.begin(), chosenId.end(), '\t'), chosenId.end());
			//Clear Buffer
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');

			if (productFile.is_open())
			{

				getline(productFile, line); //Skip the header row

				while (getline(productFile, line))
				{
					stringstream lineStream(line);
					string productId;

					getline(lineStream, productId, '\t');

					if (chosenId == productId)
					{

						string name, categoryId, itemPrice, packagingPrice, qty, details;
						// Read each cell (column) from the line
						this->productId = productId;
						getline(lineStream, this->name, '\t');
						getline(lineStream, this->categoryId, '\t');
						getline(lineStream, itemPrice, '\t');
						getline(lineStream, packagingPrice, '\t');
						getline(lineStream, qty, '\t');
						getline(lineStream, this->details, '\t');

						this->itemPrice = stof(itemPrice);
						this->packagingPrice = stof(packagingPrice);
						this->qty = stoi(qty);
						productFile.close();

						return;
					}
				}
				productFile.clear(); // Clear any existing flags
				productFile.seekg(0, ios::beg); // Move cursor to the beginning of the file
				cout << "\nProduct ID is invalid. Please enter a valid ID." << endl;
			}
		}

	}

	bool updateProduct()
	{
		// Open the original file for reading
		ifstream productFile("files/Products.txt");
		ifstream orderFile("files/Orders.txt");

		// check if file is open
		if (!productFile.is_open())
			return false;
		if (!orderFile.is_open())
			return false;

		// Create a temporary file for writing the updated data
		ofstream tempProductFile("files/tempProducts.txt");
		ofstream tempOrderFile("files/tempOrders.txt");

		// check if file is open
		if (!tempProductFile.is_open())
		{
			productFile.close();
			return false;
		}
		if (!tempOrderFile.is_open())
		{
			orderFile.close();
			return false;
		}

		// Read the lines from the original file
		string line;
		while (getline(productFile, line))
		{
			stringstream lineStream(line);
			string productId, name, categoryId, itemPrice, packagingPrice, qty, details;

			// Read each cell (column) from the line
			getline(lineStream, productId, '\t');
			getline(lineStream, name, '\t');
			getline(lineStream, categoryId, '\t');
			getline(lineStream, itemPrice, '\t');
			getline(lineStream, packagingPrice, '\t');
			getline(lineStream, qty, '\t');
			getline(lineStream, details, '\t');

			// Check if the userId from the file matches the userId of the current User object
			if (productId == this->productId)
			{
				// If it matches, write the updated data to the temp file
				tempProductFile << this->productId << "\t" << this->name << "\t" << this->categoryId << "\t" << fixed << setprecision(2) 
					<< this->itemPrice << "\t" << fixed << setprecision(2) << this->packagingPrice << "\t" << this->qty << "\t" << this->details << endl;
			}
			else
			{
				// If it doesn't match, write the original data to the temp file
				tempProductFile << productId << "\t" << name << "\t" << categoryId << "\t" << itemPrice << "\t" 
					<< packagingPrice << "\t" << qty << "\t" << details << endl;
			}
		}

		// Edit order history in orders.txt
		// Read the lines from the original file
		while (getline(orderFile, line))
		{
			stringstream lineStream(line);
			string orderId, productId, productName, customerId, qty, status, itemPrice, packagingPrice, totalPrice;

			// Read each cell (column) from the line
			getline(lineStream, orderId, '\t');
			getline(lineStream, productId, '\t');
			getline(lineStream, productName, '\t');
			getline(lineStream, customerId, '\t');
			getline(lineStream, qty, '\t');
			getline(lineStream, status, '\t');

			if ((status == "Card" or status == "COD") and productId == this->productId)
			{
				getline(lineStream, itemPrice, '\t');
				getline(lineStream, packagingPrice, '\t');
				getline(lineStream, totalPrice, '\t');
				tempOrderFile << orderId << "\t" << productId << "\t" << this->name << "\t" << customerId << "\t" << qty << "\t" 
					<< status << "\t" << itemPrice << "\t" << packagingPrice << "\t" << totalPrice << endl;

			}
			else if (status == "Cart" and productId == this->productId)
			{
				tempOrderFile << orderId << "\t" << productId << "\t" << this->name << "\t" << customerId << "\t" << qty << "\t" << status << endl;

			}
			else
			{
				tempOrderFile << line << endl;
			}
		}

		// Close the original file and the temp file
		productFile.close();
		tempProductFile.close();
		orderFile.close();
		tempOrderFile.close();

		// Remove the original file
		if (remove("files/Products.txt") != 0)
			return false;

		if (remove("files/Orders.txt") != 0)
			return false;

		// Rename the temp file to the original file name
		if (rename("files/tempProducts.txt", "files/Products.txt") != 0)
			return false;

		if (rename("files/tempOrders.txt", "files/Orders.txt") != 0)
			return false;

		return true;
	}

	bool deleteProduct()
	{
		// Open the original file for reading
		ifstream productFile("files/Products.txt");
		ifstream orderFile("files/Orders.txt");

		// check if file is open
		if (!productFile.is_open())
		{
			return false;
		}

		// check if file is open
		if (!orderFile.is_open())
		{
			return false;
		}

		// Create a temporary file for writing the updated data
		ofstream tempProductFile("files/tempProducts.txt");
		ofstream tempOrderFile("files/tempOrders.txt");

		// check if file is open
		if (!tempProductFile.is_open())
		{
			productFile.close();
			return false;
		}

		// check if file is open
		if (!tempOrderFile.is_open())
		{
			orderFile.close();
			return false;
		}

		string line;

		// Edit order history in orders.txt
		// Read the lines from the original file
		while (getline(orderFile, line))
		{
			stringstream lineStream(line);
			string orderId, productId, productName, customerId, qty, status, itemPrice, packagingPrice, totalPrice;

			// Read each cell (column) from the line
			getline(lineStream, orderId, '\t');
			getline(lineStream, productId, '\t');
			getline(lineStream, productName, '\t');
			getline(lineStream, customerId, '\t');
			getline(lineStream, qty, '\t');
			getline(lineStream, status, '\t');


			if ((status == "Card" or status == "COD") and productId == this->productId)
			{
				getline(lineStream, itemPrice, '\t');
				getline(lineStream, packagingPrice, '\t');
				getline(lineStream, totalPrice, '\t');
				tempOrderFile << orderId << "\t" << "0000" << "\t" << productName << "\t" << customerId << "\t" << qty << "\t" 
					<< status << "\t" << itemPrice << "\t" << packagingPrice << "\t" << totalPrice << endl;

			} // cart item will be removed when the user opens for the next time
			else
			{
				tempOrderFile << line << endl;
			}
		}

		// Delete the product from products.txt
		// Read the lines from the original file
		while (getline(productFile, line))
		{
			stringstream lineStream(line);
			string productId, name, categoryId, itemPrice, packagingPrice, qty, description;

			// Read each cell (column) from the line
			getline(lineStream, productId, '\t');
			getline(lineStream, name, '\t');
			getline(lineStream, categoryId, '\t');
			getline(lineStream, itemPrice, '\t');
			getline(lineStream, packagingPrice, '\t');
			getline(lineStream, qty, '\t');
			getline(lineStream, description, '\t');

			// Check if the userId from the file matches the userId of the current User object
			if (productId != this->productId)
			{
				// If it doesn't match, write the original data to the temp file
				// Otherwise skip
				tempProductFile << productId << "\t" << name << "\t" << categoryId << "\t" << itemPrice << "\t" 
					<< packagingPrice << "\t" << qty << "\t" << description << endl;
			}
		}

		// Close the original file and the temp file
		productFile.close();
		tempProductFile.close();
		orderFile.close();
		tempOrderFile.close();

		// Remove the original file
		if (remove("files/Products.txt") != 0)
			return false;

		if (remove("files/Orders.txt") != 0)
			return false;

		// Rename the temp file to the original file name
		if (rename("files/tempProducts.txt", "files/Products.txt") != 0)
			return false;

		if (rename("files/tempOrders.txt", "files/Orders.txt") != 0)
			return false;

		return true;
	}

	void editProduct()
	{
		string edit = "";

		do
		{
			Category category(this->categoryId);


			cout << ".~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~." << endl;
			cout << "|                           PRODUCT DETAILS                            |" << endl;
			cout << ".~~~~~~~~~~~~~~~~~~~~~.~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~." << endl;
			cout << "| 1. Product ID       | " << setw(46) << this->categoryId << " |" << endl;
			cout << "| 2. Product Name     | " << setw(46) << this->name << " |" << endl;
			cout << "| 3. Category ID      | " << setw(46) << this->categoryId << " |" << endl;
			cout << "| 4. Category Name    | " << setw(46) << category.name << " |" << endl;
			cout << "| 5. Item Price       | RM " << setw(43) << this->itemPrice << " |" << endl;
			cout << "| 6. Packaging Price  | RM " << setw(43) << this->packagingPrice << " |" << endl;
			cout << "| 7. Quantity         | " << setw(46) << this->qty << " |" << endl;
			cout << "| 8. Details          | " << setw(46) << this->details << " |" << endl;
			cout << ".~~~~~~~~~~~~~~~~~~~~~.~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~." << endl;

			cout << "Which data do you want to edit? : ";

			string option = "";
			cin >> option;

			//Clear Buffer
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');

			//Get the update from user
			if (option == "1")
				cout << "Product ID cannot be edited!" << endl;
			else if (option == "2")
				this->setName();
			else if (option == "3" or option == "4")
				this->setCategory();
			else if (option == "5")
				this->setItemPrice();
			else if (option == "6")
				this->setPackagingPrice();
			else if (option == "7")
				this->setQty();
			else if (option == "8")
				this->setDetails();
			else
				cout << "\nEnter a valid input." << endl;

			cout << "Do you want to continue editing? [Y/N]: ";
			cin >> edit;

			//Clear Buffer
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');

			for (int i = 0; i < edit.length(); i++)
				edit[i] = tolower(edit[i]);

		} while (edit == "y" or edit == "yes");
	}
};

class User
{
public:
	string userId;
	string email;
	string password;
	string userType; //customer, admin, manager//


	User()
	{

	}

	User(string userId, string email, string password, string userType) 
	{
		this->userId = userId;
		this->email = email;
		this->password = password;
		this->userType = userType;
	
	}

	bool verifyPassword()
	{
		string line;
		ifstream usersFile("files/Users.txt");

		if (usersFile.is_open())
		{
			// Skip the first line (header row)
			getline(usersFile, line);
			// Read the rest of the lines (data rows)
			while (getline(usersFile, line))
			{
				stringstream lineStream(line);
				string userId, email, password, userType; 
				// Read each cell (column) from the line
				getline(lineStream, userId, '\t');
				getline(lineStream, email, '\t');
				getline(lineStream, password, '\t');
				getline(lineStream, userType, '\t');
				

				if (email == this->email and password == this->password)
				{
					this->userId = userId;
					this->userType = userType;
					
					usersFile.close();
					return true;
				}

			}
			usersFile.close();
		}

		return false;
	}

	bool addUser()
	{
		this->userId = generateId("files/Users.txt");

		//Write into file
		ofstream userFile("files/Users.txt", ios::app);
		if (userFile.is_open())
		{
			userFile << this->userId << "\t" << this->email << "\t" << this->password << "\t" << this->userType << endl; 
			userFile.close();
			return true;
		}
		//If everything goes well return true
		return false;
	}

	bool updateUser()
	{
		// Open the original file for reading
		ifstream userFile("files/Users.txt");
		if (!userFile.is_open())
			return false;

		// Create a temporary file for writing the updated data
		ofstream tempUserFile("files/tempUsers.txt");
		if (!tempUserFile.is_open())
		{
			userFile.close();
			return false;
		}

		// Read the lines from the original file
		string line;
		while (getline(userFile, line))
		{
			stringstream lineStream(line);
			string userId, email, password, userType;

			// Read each cell (column) from the line
			getline(lineStream, userId, '\t');
			getline(lineStream, email, '\t');
			getline(lineStream, password, '\t');
			getline(lineStream, userType, '\t');
			

			// Check if the userId from the file matches the userId of the current User object
			if (userId == this->userId)
			{
				// If it matches, write the updated data to the temp file
				tempUserFile << this->userId << "\t" << this->email << "\t" << this->password << "\t" << this->userType <<endl;
				
			}
			else {
				// If it doesn't match, write the original data to the temp file
				tempUserFile << userId << "\t" << email << "\t" << password << "\t" << userType << endl;
			
			}
		}

		// Close the original file and the temp file
		userFile.close();
		tempUserFile.close();

		// Remove the original file
		if (remove("files/Users.txt") != 0)
		{
			return false;
		}

		// Rename the temp file to the original file name
		if (rename("files/tempUsers.txt", "files/Users.txt") != 0)
		{
			return false;
		}

		return true;
	}

	bool deleteUser()
	{
		// Open the original file for reading
		ifstream userFile("files/Users.txt");

		// check if file is open
		if (!userFile.is_open())
		{
			return false;
		}

		// Create a temporary file for writing the updated data
		ofstream tempUserFile("files/tempUsers.txt");

		// check if file is open
		if (!tempUserFile.is_open())
		{
			userFile.close();
			return false;
		}

		// Read the lines from the original file
		string line;
		while (getline(userFile, line))
		{
			stringstream lineStream(line);
			string userId, email, password, userType; 

			// Read each cell (column) from the line
			getline(lineStream, userId, '\t');
			getline(lineStream, email, '\t');
			getline(lineStream, password, '\t');
			getline(lineStream, userType, '\t');
			

			// Check if the userId from the file matches the userId of the current User object
			if (userId != this->userId)
			{
				// If it doesn't match, write the original data to the temp file
				// Otherwise skip
				tempUserFile << userId << "\t" << email << "\t" << password << "\t"
					<< userType << endl; 
			}

		}

		// Close the original file and the temp file
		userFile.close();
		tempUserFile.close();

		// Remove the original file
		if (remove("files/Users.txt") != 0)
		{
			return false;
		}

		// Rename the temp file to the original file name
		if (rename("files/tempUsers.txt", "files/Users.txt") != 0)
		{
			return false;
		}

		return true;

	}

//important!
	void setEmail()
	{
		regex emailRegex("^[a-zA-Z0-9_.+~]+@[a-zA-Z0-9-]+\\.[a-zA-Z0-9-.]+$");
		while (true)
		{
			cout << "Enter email address: ";

			getline(cin, this->email);
			this->email.erase(std::remove(this->email.begin(), this->email.end(), '\t'), this->email.end());
			//converting email to lower case
			for (int i = 0; i < this->email.length(); i++)
			{
				this->email[i] = tolower(this->email[i]);
			}

			//Validate the email
			if (regex_match(this->email, emailRegex))
			{
				break;
			}

			cout << "Invalid email address. Please try again." << endl;
		}
	}

	bool setNewEmail()
	{
		regex emailRegex("^[a-zA-Z0-9_.+~]+@[a-zA-Z0-9-]+\\.[a-zA-Z0-9-.]+$");
		while (true)
		{
			cout << "\nEnter an email address: ";
			string newEmail;
			getline(cin, newEmail);

			newEmail.erase(std::remove(newEmail.begin(), newEmail.end(), '\t'), newEmail.end());
			//converting email to lower case
			for (int i = 0; i < newEmail.length(); i++)
			{
				newEmail[i] = tolower(newEmail[i]);
			}
			//Validate the email
			if (!regex_match(newEmail, emailRegex))
			{
				cout << "\nInvalid email address. Please try again." << endl;
				continue;
			}

			// Open the file for reading
			ifstream userFile("files/Users.txt");

			string line, userId, email;
			//Skip the header row
			getline(userFile, line);

			if (userFile.is_open())
			{
				while (getline(userFile, line))
				{
					stringstream lineStream(line);

					getline(lineStream, userId, '\t');
					getline(lineStream, email, '\t');

					if (email == newEmail && userId != this->userId)
					{
						cout << "\nEmail already is in use." << endl;
						userFile.close();
						return false;
					}
				}
				userFile.close();
			}
			this->email = newEmail;
			return true;
		}
	}

	void setPassword()
	{
		while (true)
		{
			this->password = "";
			// Prompt the user to enter password
			cout << "Enter password: ";

			// Read characters from the console until the user presses Enter

			char c = _getch();
			while (c != '\r')
			{
				if (c == '\b')
				{
					// The user pressed Backspace, delete the last character from the password string
					if (!this->password.empty())
					{
						this->password.pop_back();
						cout << "\b \b"; // Overwrite the last character with a space and then move the cursor back
					}
				}
				else
				{
					// The user entered a character, append it to the password string
					this->password += c;
					cout << '*'; // Print an asterisk to obscure the password
				}
				c = _getch();
			}
			cout << endl;
			password.erase(std::remove(password.begin(), password.end(), '\t'), password.end());
			if (this->password.empty())
				cout << "Password cannot be empty. Please try again." << endl;
			else
				break;
		}



	}

	void setNewPassword()
	{
		// Regex for a password that is 8-25 characters long and contains at least one
		// uppercase letter, one lowercase letter, one digit, and one special character

		regex passwordRegex(R"(^(?=.*[A-Z])(?=.*[a-z])(?=.*\d)(?=.*[!@#$&_-])[A-Za-z\d!@#$&_-]{8,25}$)");
		while (true)
		{
			// Print password requirements to the console
			cout << "\nPassword requirements:" << endl;
			cout << "\t-Length: 8-25 characters" << endl;
			cout << "\t-At least one uppercase letter" << endl;
			cout << "\t-At least one lowercase letter" << endl;
			cout << "\t-At least one special character[!@#$&_-]" << endl;

			// Prompt the user to enter a password
			cout << "\nEnter password: ";

			// Clear the password string
			this->password = "";

			// Read characters from the console until the user presses Enter
			char c = _getch();
			while (c != '\r')
			{
				if (c == '\b')
				{
					// The user pressed Backspace, delete the last character from the password string
					if (!this->password.empty())
					{
						this->password.pop_back();
						cout << "\b \b"; // Overwrite the last character with a space and then move the cursor back
					}
				}
				else
				{
					// The user entered a character, append it to the password string
					this->password += c;
					cout << '*'; // Print an asterisk to obscure the password
				}
				c = _getch();
			}
			cout << endl;

			this->password.erase(std::remove(this->password.begin(), this->password.end(), '\t'), this->password.end());

			// Validate the password against the regex pattern
			if (regex_match(this->password, passwordRegex))
			{
				// Password is valid, exit the loop
				break;
			}
			// Print an error message if the password is invalid
			cout << "Invalid password. Please try again." << endl;
		}

	}

	bool confirmPass()
	{

		string passwordConfirm;
		// Read characters from the console until the user presses Enter
		while (true)
		{
			cout << "\nEnter the password again: ";
			char c = _getch();
			while (c != '\r')
			{
				if (c == '\b')
				{
					// The user pressed Backspace, delete the last character from the password string
					if (!passwordConfirm.empty())
					{
						passwordConfirm.pop_back();
						cout << "\b \b"; // Overwrite the last character with a space and then move the cursor back
					}
				}
				else
				{
					// The user entered a character, append it to the password string
					passwordConfirm += c;
					cout << '*'; // Print an asterisk to obscure the password
				}
				c = _getch();
			}
			cout << endl;

			passwordConfirm.erase(std::remove(passwordConfirm.begin(), passwordConfirm.end(), '\t'), passwordConfirm.end());
			if (passwordConfirm.empty())
				cout << "\nThis field cannot be empty." << endl;
			else
				break;

		}
		if (passwordConfirm == this->password)
			return true;
		else
		{
			cout << "\nPasswords did not match. Try again." << endl;
			return false;
		}


	}

	void getUserData()
	{
		ifstream userFile("files/Users.txt");

		if (userFile.is_open())
		{
			string line;
			//Read the first line
			getline(userFile, line);
			// Read the lines from file
			while (getline(userFile, line))
			{
				stringstream lineStream(line);
				// Read each cell (column) from the line
				string email;
				getline(lineStream, this->userId, '\t'); // Skip the first column
				getline(lineStream, email, '\t'); // Read the email from the second column

				if (this->email == email)
				{
					getline(lineStream, this->password, '\t');
					getline(lineStream, this->userType, '\t');
					
					break;
				}

			}
			userFile.close();
		}
	}

};

class Customer : public User
{
public:
	string customerId;
	string name;
	string phone;
	string address;

public:
	Customer()
	{
		this->userType = "customer";
	}

	Customer(string idOrEmail)
	{
		string line;
		ifstream customerFile("files/Customers.txt");

		if (customerFile.is_open())
		{

			getline(customerFile, line); //Skip the header row

			while (getline(customerFile, line))
			{
				stringstream lineStream(line);
				string customerId, email;

				getline(lineStream, customerId, '\t');
				getline(lineStream, email, '\t');

				if (idOrEmail == customerId or idOrEmail == email)
				{

					// Read each cell (column) from the line
					this->customerId = customerId;
					this->email = email;
					getline(lineStream, this->name, '\t');
					getline(lineStream, this->phone, '\t');
					getline(lineStream, this->address, '\t');
					customerFile.close();

					getUserData();
					return;
				}
			}

		}
	}

	Customer(string customerId, string email, string name, string phone, string address)
	{
		this->customerId = customerId;
		this->name = name;
		this->email = email;
		this->phone = phone;
		this->address = address;


		ifstream userFile("files/Users.txt");


		if (userFile.is_open())
		{
			string line;
			//Read the first line
			getline(userFile, line);
			// Read the lines from file
			while (getline(userFile, line))
			{
				stringstream lineStream(line);
				// Read each cell (column) from the line
				string email;
				getline(lineStream, this->userId, '\t'); // Skip the first column
				getline(lineStream, email, '\t'); // Read the email from the second column

				if (this->email == email)
				{
					getline(lineStream, this->password, '\t');
					getline(lineStream, this->userType, '\t');

					break;
				}

			}
			userFile.close();
		}
	}

	void setName()
	{
		// Keep asking for input until the user enters a non-empty name
		while (true)
		{
			cout << "Enter Name: ";
			getline(cin, this->name);
			this->name.erase(std::remove(this->name.begin(), this->name.end(), '\t'), this->name.end());
			if (!this->name.empty())
			{
				// Name is not empty, exit loop
				break;
			}
			cout << "\nThis field cannot be empty." << endl;
		}
	}

	void setPhone()
	{
		// Regular expression pattern for a phone number
		regex phoneRegex("^[0-9]+$");

		while (true)
		{
			cout << "\nEnter phone number: ";

			getline(cin, this->phone);
			this->phone.erase(std::remove(this->phone.begin(), this->phone.end(), '\t'), this->phone.end());
			if (regex_match(this->phone, phoneRegex))
			{
				// Phone number is valid, return it
				return;
			}

			cout << "Invalid phone number. Please try again." << endl;
		}
	}

	void setAddress()
	{
		// Keep asking for input until the user enters a non-empty address
		while (true)
		{
			cout << "\nEnter Address: ";
			getline(cin, this->address);
			this->address.erase(std::remove(this->address.begin(), this->address.end(), '\t'), this->address.end());
			if (!this->address.empty())
			{
				// Address is not empty, exit loop
				break;
			}
			cout << "\nAddress cannot be empty" << endl;
		}
	}

	bool addCustomer()
	{

		this->customerId = generateId("files/Customers.txt");

		//Write into file
		ofstream customerFile("files/Customers.txt", ios::app);

		if (customerFile.is_open())
		{

			customerFile << this->customerId << "\t" << this->email << "\t" << this->name << "\t" << this->phone << "\t" << this->address << endl;

			customerFile.close();
			return true;
		}
		//If everything goes well return true
		return false;
	}

	bool updateCustomer()
	{

		// Open the original file for reading
		ifstream customerFile("files/Customers.txt");

		// check if file is open
		if (!customerFile.is_open())
		{
			return false;
		}

		// Create a temporary file for writing the updated data
		ofstream tempCustomerFile("files/tempCustomers.txt");

		// check if file is open
		if (!tempCustomerFile.is_open())
		{
			customerFile.close();
			return false;
		}

		// Read the lines from the original file
		string line;
		while (getline(customerFile, line))
		{
			stringstream lineStream(line);
			string customerId, email, name, phone, address;

			// Read each cell (column) from the line
			getline(lineStream, customerId, '\t');
			getline(lineStream, email, '\t');
			getline(lineStream, name, '\t');
			getline(lineStream, phone, '\t');
			getline(lineStream, address, '\t');

			// Check if the userId from the file matches the userId of the current User object
			if (customerId == this->customerId)
			{
				// If it matches, write the updated data to the temp file
				tempCustomerFile << this->customerId << "\t" << this->email << "\t" << this->name << "\t" << this->phone << "\t" << this->address << endl;
			}
			else {
				// If it doesn't match, write the original data to the temp file
				tempCustomerFile << customerId << "\t" << email << "\t" << name << "\t" << phone << "\t" << address << endl;
			}
		}

		// Close the original file and the temp file
		customerFile.close();
		tempCustomerFile.close();

		// Remove the original file
		if (remove("files/Customers.txt") != 0)
		{
			return false;
		}

		// Rename the temp file to the original file name
		if (rename("files/tempCustomers.txt", "files/Customers.txt") != 0)
		{
			return false;
		}

		return true;
	}

	bool deleteCustomer()
	{
		// Open the original file for reading
		ifstream customerFile("files/Customers.txt");
		ifstream orderFile("files/Orders.txt");

		// check if file is open
		if (!customerFile.is_open())
		{
			return false;
		}
		if (!orderFile.is_open())
		{
			return false;
		}

		// Create a temporary file for writing the updated data
		ofstream tempCustomerFile("files/tempCustomers.txt");
		ofstream tempOrderFile("files/tempOrders.txt");

		// check if file is open
		if (!tempCustomerFile.is_open())
		{
			customerFile.close();
			return false;
		}
		if (!tempOrderFile.is_open())
		{
			orderFile.close();
			return false;
		}

		// Read the lines from the original file
		string line;
		while (getline(customerFile, line))
		{
			stringstream lineStream(line);
			string customerId, email, name, phone, address;

			// Read each cell (column) from the line
			getline(lineStream, customerId, '\t');
			getline(lineStream, email, '\t');
			getline(lineStream, name, '\t');
			getline(lineStream, phone, '\t');
			getline(lineStream, address, '\t');

			// Check if the userId from the file matches the userId of the current User object
			if (customerId != this->customerId)
			{
				// If it doesn't match, write the original data to the temp file
				// Otherwise skip
				tempCustomerFile << customerId << "\t" << email << "\t" << name << "\t" << phone << "\t" << address << endl;
			}
		}
		// Edit order history in orders.txt
		// Read the lines from the original file
		while (getline(orderFile, line))
		{
			stringstream lineStream(line);
			string orderId, productId, productName, customerId, qty, status, itemPrice, packagingPrice, totalPrice;

			// Read each cell (column) from the line
			getline(lineStream, orderId, '\t');
			getline(lineStream, productId, '\t');
			getline(lineStream, productName, '\t');
			getline(lineStream, customerId, '\t');
			getline(lineStream, qty, '\t');
			getline(lineStream, status, '\t');


			if ((status == "Card" or status == "COD") and customerId == this->customerId)
			{
				getline(lineStream, itemPrice, '\t');
				getline(lineStream, packagingPrice, '\t');
				getline(lineStream, totalPrice, '\t');
				tempOrderFile << orderId << "\t" << productId << "\t" << productName << "\t" << "0000" << "\t" << qty << "\t" << status << "\t" << itemPrice << "\t" << packagingPrice << "\t" << totalPrice << endl;

			}
			else if (status == "Cart" and customerId == this->customerId)
			{
				//orderFile 
			}
			else
			{
				tempOrderFile << line << endl;
			}
		}

		// Close the original file and the temp file
		customerFile.close();
		tempCustomerFile.close();
		orderFile.close();
		tempOrderFile.close();

		// Remove the original file
		if (remove("files/Customers.txt") != 0)
		{
			return false;
		}
		if (remove("files/Orders.txt") != 0)
			return false;

		// Rename the temp file to the original file name
		if (rename("files/tempCustomers.txt", "files/Customers.txt") != 0)
		{
			return false;
		}

		if (rename("files/tempOrders.txt", "files/Orders.txt") != 0)
			return false;


		return true;
	}

	int countCustomer()
	{
		string line;
		ifstream customerFile("files/Customers.txt");

		//Read the first line
		getline(customerFile, line);

		int customerCount = 0;

		if (customerFile.is_open())
		{
			// Get the number of managers
			while (getline(customerFile, line))
			{
				customerCount++;
			}
			customerFile.close();
		}

		return customerCount;
	}

	void showAllCustomers()
	{
		string line;
		ifstream customerFile("files/Customers.txt");


		if (customerFile.is_open())
		{
			cout << endl;
			int customerCount = 0;
			// Read the lines from file
			getline(customerFile, line);
			cout << ".~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~." << endl;
			cout << "|                                                             CUSTOMERS                                                             |" << endl;
			cout << ".~~~~~~~~~~~~~.~~~~~~~~~~~~~~~~~~~~~~~~.~~~~~~~~~~~~~~~~~~~~~~~~.~~~~~~~~~~~~~~~~~~.~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~." << endl;
			cout << "| Customer ID | Email Address          | Name                   | Phone Number     | Address                                        |" << endl;
			cout << ".~~~~~~~~~~~~~.~~~~~~~~~~~~~~~~~~~~~~~~.~~~~~~~~~~~~~~~~~~~~~~~~.~~~~~~~~~~~~~~~~~~.~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~." << endl;
			while (getline(customerFile, line))
			{
				stringstream lineStream(line);
				string customerId, email, name, phone, address;
				// Read each cell (column) from the line
				getline(lineStream, customerId, '\t');
				getline(lineStream, email, '\t');
				getline(lineStream, name, '\t');
				getline(lineStream, phone, '\t');
				getline(lineStream, address, '\t');

				cout << "|    " << customerId
					<< "     | " << setw(22) << left << email
					<< " | " << setw(22) << left << name
					<< " | " << setw(16) << left << phone
					<< " | " << setw(46) << left << address << " |" << endl;

				customerCount++;


			}
			cout << ".~~~~~~~~~~~~~.~~~~~~~~~~~~~~~~~~~~~~~~.~~~~~~~~~~~~~~~~~~~~~~~~.~~~~~~~~~~~~~~~~~~.~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~." << endl;
			cout << endl << "Total Customers: " << customerCount << endl << endl;
			customerFile.close();
		}
	}

	void chooseCustomer()
	{
		string line, chosenId;
		ifstream customerFile("files/Customers.txt");

		while (true)
		{

			cout << "\nEnter Customer ID: ";
			cin >> chosenId;
			chosenId.erase(std::remove(chosenId.begin(), chosenId.end(), '\t'), chosenId.end());
			//Clear Buffer
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');

			if (customerFile.is_open())
			{

				getline(customerFile, line); //Skip the header row

				while (getline(customerFile, line))
				{
					stringstream lineStream(line);
					string customerId;

					getline(lineStream, customerId, '\t');

					if (chosenId == customerId)
					{

						string email, name, phone, address;
						// Read each cell (column) from the line
						this->customerId = customerId;
						getline(lineStream, this->email, '\t');
						getline(lineStream, this->name, '\t');
						getline(lineStream, this->phone, '\t');
						getline(lineStream, this->address, '\t');
						customerFile.close();

						getUserData();
						return;
					}
				}
				customerFile.clear(); // Clear any existing flags
				customerFile.seekg(0, ios::beg); // Move cursor to the beginning of the file
				cout << "\nInvalid Customer ID. Please try again." << endl;
			}
		}
	}

	void editCustomer()
	{
		string edit = "";

		do
		{
			
			cout << ".~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~." << endl;
			cout << "|          CUSTOMER DETAILS                                         |" << endl;
			cout << ".~~~~~~~~~~~~~~~~~~.~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~." << endl;
			cout << "| 1. User ID       | " << setw(46) << left << this->userId << " |" << endl;
			cout << "| 2. Customer ID   | " << setw(46) << left << this->customerId << " |" << endl;
			cout << "| 3. Name          | " << setw(46) << left << this->name << " |" << endl;
			cout << "| 4. Email Address | " << setw(46) << left << this->email << " |" << endl;
			cout << "| 5. Phone Number  | " << setw(46) << left << this->phone << " |" << endl;
			cout << "| 6. Address       | " << setw(46) << left << this->address << " |" << endl;
			cout << "| 7. Reset Password " << setw(46) << left << "" << "  |" << endl;
			cout << ".~~~~~~~~~~~~~~~~~~.~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~." << endl;

			cout << "\nWhich data do you want to edit? : ";

			string option = "";
			cin >> option;

			//Clear Buffer
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');

			//Get the update from user
			if (option == "1")
				cout << "\nUser ID is not editable" << endl;
			else if (option == "2")
				cout << "\nCustomer ID is not editable" << endl;
			else if (option == "3")
				this->setName();
			else if (option == "4")
				this->setNewEmail();
			else if (option == "5")
				this->setPhone();
			else if (option == "6")
				this->setAddress();
			else if (option == "7")
			{
				do
				{
					this->setNewPassword();
				} while (!this->confirmPass());
			}
			else
				cout << "\nInvalid input. Try again" << endl;

			cout << "\nDo you want to continue editing? [Y/N]: ";
			cin >> edit;

			//Clear Buffer
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');

			for (int i = 0; i < edit.length(); i++)
				edit[i] = tolower(edit[i]);
			this->updateCustomer();
			this->updateUser();
		} while (edit == "y" or edit == "yes");
	}

	void editPersonalDetails()
	{
		string edit = "";

		do
		{

			cout << ".~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~." << endl;
			cout << "|                    PERSONAL DETAILS                               |" << endl;
			cout << ".~~~~~~~~~~~~~~~~~~.~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~." << endl;
			cout << "| 1. Name          | " << setw(46) << left << this->name << " |" << endl;
			cout << "| 2. Email Address | " << setw(46) << left << this->email << " |" << endl;
			cout << "| 3. Phone Number  | " << setw(46) << left << this->phone << " |" << endl;
			cout << "| 4. Address       | " << setw(46) << left << this->address << " |" << endl;
			cout << "| 5. Reset Password   " << setw(46) << left << "" << "|" << endl;
			cout << ".~~~~~~~~~~~~~~~~~~.~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~." << endl;
			
			cout << "\nWhich data do you want to edit? : ";

			string option = "";
			cin >> option;

			//Clear Buffer
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');

			//Get the update from user
			if (option == "1")
				this->setName();
			else if (option == "2")
				this->setNewEmail();
			else if (option == "3")
				this->setPhone();
			else if (option == "4")
				this->setAddress();
			else if (option == "5")
			{
			    this->setPassword();
				if (this->verifyPassword())
					{
						do
						{
							this->setNewPassword();
						} while (!this->confirmPass());
					}
					else
						cout << "\nPassword did not match." << endl;
			}
			
			else
			{
				cout << "\nInvalid input. Try again" << endl;
			}


			cout << "\nDo you want to continue editing? [Y/N]: ";
			cin >> edit;

			//Clear Buffer
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');

			for (int i = 0; i < edit.length(); i++)
				edit[i] = tolower(edit[i]);
			this->updateCustomer();
			this->updateUser();
		} while (edit == "y" or edit == "yes");
	}

	void searchCustomer(string search)
	{
		string line;
		ifstream customerFile("files/Customers.txt");


		//converting search key to lower case
		for (int i = 0; i < search.length(); i++)
			search[i] = tolower(search[i]);

		if (customerFile.is_open())
		{
			cout << endl;
			int customerCount = 0;
			// Read the lines from file
			cout << ".~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~." << endl;
			cout << "|                                                             CUSTOMERS                                                             |" << endl;
			cout << ".~~~~~~~~~~~~~.~~~~~~~~~~~~~~~~~~~~~~~~.~~~~~~~~~~~~~~~~~~~~~~~~.~~~~~~~~~~~~~~~~~~.~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~." << endl;
			cout << "| Customer ID | Email Address          | Name                   | Phone Number     | Address                                        |" << endl;
			cout << ".~~~~~~~~~~~~~.~~~~~~~~~~~~~~~~~~~~~~~~.~~~~~~~~~~~~~~~~~~~~~~~~.~~~~~~~~~~~~~~~~~~.~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~." << endl;
			getline(customerFile, line);
			while (getline(customerFile, line))
			{
				stringstream lineStream(line);
				string customerId, email, name, phone, address;
				// Read each cell (column) from the line
				getline(lineStream, customerId, '\t');
				getline(lineStream, email, '\t');
				getline(lineStream, name, '\t');
				getline(lineStream, phone, '\t');
				getline(lineStream, address, '\t');

				for (int i = 0; i < line.length(); i++)
					line[i] = tolower(line[i]);

				if (line.find(search) != string::npos or customerId == "Customer ID")
				{
				
					cout << "|    " << customerId
						<< "     | " << setw(22) << left << email
						<< " | " << setw(22) << left << name
						<< " | " << setw(16) << left << phone
						<< " | " << setw(46) << left << address << " |" << endl;

					customerCount++;
				}
			}
			cout << ".~~~~~~~~~~~~~.~~~~~~~~~~~~~~~~~~~~~~~~.~~~~~~~~~~~~~~~~~~~~~~~~.~~~~~~~~~~~~~~~~~~.~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~." << endl;
			cout << endl << "\nTotal no. of customers found: " << customerCount << endl << endl;
			customerFile.close();
		}
	}
};

class Admin : public User
{
public:
	Admin()
	{
		this->userId = "0001";
		ifstream userFile("files/Users.txt");

		if (userFile.is_open())
		{
			string line;
			//Read the first line
			getline(userFile, line);
			// Read the lines from file
			while (getline(userFile, line))
			{
				stringstream lineStream(line);
				// Read each cell (column) from the line
				string userId;
				getline(lineStream, userId, '\t');

				if (userId == this->userId)
				{
					getline(lineStream, this->email, '\t');
					getline(lineStream, this->password, '\t');
					getline(lineStream, this->userType, '\t');
					
					break;
				}

			}
			userFile.close();
		}
	}
};

class Manager : public User
{
public:
	string managerId;
	string name;
	string phone;
	string ic;
	string address;


	Manager()
	{
		this->userType = "manager";
	}

	Manager(string idOrEmail)
	{
		string line;
		ifstream managerFile("files/Managers.txt");

		if (managerFile.is_open())
		{

			getline(managerFile, line); //Skip the header row

			while (getline(managerFile, line))
			{
				stringstream lineStream(line);
				string managerId, email;

				getline(lineStream, managerId, '\t');
				getline(lineStream, email, '\t');

				if (idOrEmail == managerId or idOrEmail == email)
				{

					// Read each cell (column) from the line
					this->managerId = managerId;
					this->email = email;
					getline(lineStream, this->name, '\t');
					getline(lineStream, this->phone, '\t');
					getline(lineStream, this->ic, '\t');
					getline(lineStream, this->address, '\t');
					managerFile.close();

					getUserData();
					return;
				}
			}

		}
	}

	Manager(string managerId, string email, string name, string phone, string ic, string address)
	{
		this->managerId = managerId;
		this->name = name;
		this->email = email;
		this->phone = phone;
		this->ic = ic;
		this->address = address;

		getUserData();
	}

	void setName()
	{
		// Keep asking for input until the user enters a non-empty name
		while (true)
		{
			cout << "\nEnter Name: ";
			getline(cin, this->name);
			this->name.erase(std::remove(this->name.begin(), this->name.end(), '\t'), this->name.end());
			if (!this->name.empty())
			{
				// Name is not empty, exit loop
				break;
			}
			cout << "\nName cannot be empty." << endl;
		}
	}

	void setPhone()
	{
		// Regular expression pattern for a phone number
		regex phoneRegex("^[0-9]+$");

		while (true)
		{
			cout << "\nEnter phone number: ";

			getline(cin, this->phone);
			this->phone.erase(std::remove(this->phone.begin(), this->phone.end(), '\t'), this->phone.end());
			if (regex_match(this->phone, phoneRegex))
			{
				// Phone number is valid, return it
				return;
			}

			cout << "\nInvalid phone number." << endl;
		}
	}

	void setIc()
	{
		// Keep asking for input until the user enters a non-empty IC Number
		while (true)
		{
			cout << "\nEnter IC/Passport Number: ";
			getline(cin, this->ic);
			this->ic.erase(std::remove(this->ic.begin(), this->ic.end(), '\t'), this->ic.end());
			if (!this->ic.empty())
			{
				// IC Number is not empty, exit loop
				break;
			}
			cout << "\nIC/Passport Number cannot be empty." << endl;
		}
	}

	void setAddress()
	{
		// Keep asking for input until the user enters a non-empty address
		while (true)
		{
			cout << "\nEnter Address: ";
			getline(cin, this->address);
			this->address.erase(std::remove(this->address.begin(), this->address.end(), '\t'), this->address.end());
			if (!this->address.empty())
			{
				// Address is not empty, exit loop
				break;
			}
			cout << "\nAddress cannot be empty." << endl;
		}
	}

	bool addManager()
	{

		this->managerId = generateId("files/Managers.txt");

		//Write into file
		ofstream managerFile("files/Managers.txt", ios::app);

		if (managerFile.is_open())
		{
			managerFile << this->managerId << "\t" << this->email << "\t" << this->name 
				<< "\t" << this->phone << "\t" << this->ic << "\t" << this->address << endl;

			managerFile.close();
			return true;
		}
		//If everything goes well return true
		return false;
	}

	bool updateManager()
	{
		// Open the original file for reading
		ifstream managerFile("files/Managers.txt");

		// check if file is open
		if (!managerFile.is_open())
		{
			return false;
		}

		// Create a temporary file for writing the updated data
		ofstream tempManagerFile("files/tempManagers.txt");

		// check if file is open
		if (!tempManagerFile.is_open())
		{
			managerFile.close();
			return false;
		}

		// Read the lines from the original file
		string line;
		while (getline(managerFile, line))
		{
			stringstream lineStream(line);
			string managerId, email, name, phone, ic, address;

			// Read each cell (column) from the line
			getline(lineStream, managerId, '\t');
			getline(lineStream, email, '\t');
			getline(lineStream, name, '\t');
			getline(lineStream, phone, '\t');
			getline(lineStream, ic, '\t');
			getline(lineStream, address, '\t');

			// Check if the userId from the file matches the userId of the current User object
			if (managerId == this->managerId)
			{
				// If it matches, write the updated data to the temp file
				tempManagerFile << this->managerId << "\t" << this->email << "\t" << this->name 
					<< "\t" << this->phone << "\t" << this->ic << "\t" << this->address << endl;
			}
			else
			{
				// If it doesn't match, write the original data to the temp file
				tempManagerFile << managerId << "\t" << email << "\t" << name << "\t" 
					<< phone << "\t" << ic << "\t" << address << endl;
			}
		}

		// Close the original file and the temp file
		managerFile.close();
		tempManagerFile.close();

		// Remove the original file
		if (remove("files/Managers.txt") != 0)
		{
			return false;
		}
		// Rename the temp file to the original file name
		if (rename("files/tempManagers.txt", "files/Managers.txt") != 0)
		{
			return false;
		}
		return true;
	}

	bool deleteManager()
	{
		// Open the original file for reading
		ifstream managerFile("files/Managers.txt");

		// check if file is open
		if (!managerFile.is_open())
		{
			return false;
		}

		// Create a temporary file for writing the updated data
		ofstream tempManagerFile("files/tempManagers.txt");

		// check if file is open
		if (!tempManagerFile.is_open())
		{
			managerFile.close();
			return false;
		}

		// Read the lines from the original file
		string line;
		while (getline(managerFile, line))
		{
			stringstream lineStream(line);
			string managerId, email, name, phone, ic, address;

			// Read each cell (column) from the line
			getline(lineStream, managerId, '\t');
			getline(lineStream, email, '\t');
			getline(lineStream, name, '\t');
			getline(lineStream, phone, '\t');
			getline(lineStream, ic, '\t');
			getline(lineStream, address, '\t');

			// Check if the userId from the file matches the userId of the current User object
			if (managerId != this->managerId)
			{
				// If it doesn't match, write the original data to the temp file
				// Otherwise skip
				tempManagerFile << managerId << "\t" << email << "\t" << name 
					<< "\t" << phone << "\t" << ic << "\t" << address << endl;
			}
		}

		// Close the original file and the temp file
		managerFile.close();
		tempManagerFile.close();

		// Remove the original file
		if (remove("files/Managers.txt") != 0)
		{
			return false;
		}

		// Rename the temp file to the original file name
		if (rename("files/tempManagers.txt", "files/Managers.txt") != 0)
		{
			return false;
		}

		return true;
	}

	int countManager()
	{
		string line;
		ifstream managerFile("files/Managers.txt");

		//Read the first line
		getline(managerFile, line);

		int managerCount = 0;

		if (managerFile.is_open())
		{
			// Get the number of managers
			while (getline(managerFile, line))
			{
				managerCount++;
			}
			managerFile.close();
		}

		return managerCount;
	}

	void showAllManagers()
	{
		string line;
		ifstream managerFile("files/Managers.txt");


		if (managerFile.is_open())
		{
			cout << endl;
			int managerCount = 0;
			// Read the lines from file
			getline(managerFile, line);
			cout << ".~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~." << endl;
			cout << "|                                                                      MANAGERS                                                                       |" << endl;
			cout << ".~~~~~~~~~~~~.~~~~~~~~~~~~~~~~~~~~~~~~.~~~~~~~~~~~~~~~~~~~~~~~~.~~~~~~~~~~~~~~~~~~.~~~~~~~~~~~~~~~~~~.~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~." << endl;
			cout << "| Manager ID | Email Address          | Name                   | Phone Number     | IC/Passport      | Address                                        |" << endl;
			cout << ".~~~~~~~~~~~~.~~~~~~~~~~~~~~~~~~~~~~~~.~~~~~~~~~~~~~~~~~~~~~~~~.~~~~~~~~~~~~~~~~~~.~~~~~~~~~~~~~~~~~~.~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~." << endl;
			while (getline(managerFile, line))
			{
				stringstream lineStream(line);
				string managerId, email, name, phone, ic, address;
				// Read each cell (column) from the line
				getline(lineStream, managerId, '\t');
				getline(lineStream, email, '\t');
				getline(lineStream, name, '\t');
				getline(lineStream, phone, '\t');
				getline(lineStream, ic, '\t');
				getline(lineStream, address, '\t');

				cout << "|    " << managerId
					<< "    | " << setw(22) << left << email
					<< " | " << setw(22) << left << name
					<< " | " << setw(16) << left << phone
					<< " | " << setw(16) << left << ic
					<< " | " << setw(46) << left << address << " |" << endl;

				managerCount++;


			}
			cout << ".~~~~~~~~~~~~.~~~~~~~~~~~~~~~~~~~~~~~~.~~~~~~~~~~~~~~~~~~~~~~~~.~~~~~~~~~~~~~~~~~~.~~~~~~~~~~~~~~~~~~.~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~." << endl;
			cout << endl << "\nTotal no. of managers: " << managerCount << endl << endl;
			managerFile.close();
		}
	}

	void chooseManager()
	{
		string line, chosenId;
		ifstream managerFile("files/Managers.txt");

		while (true)
		{

			cout << "\nEnter Manager ID: ";
			cin >> chosenId;
			chosenId.erase(std::remove(chosenId.begin(), chosenId.end(), '\t'), chosenId.end());
			//Clear Buffer
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');

			if (managerFile.is_open())
			{

				getline(managerFile, line); //Skip the header row

				while (getline(managerFile, line))
				{
					stringstream lineStream(line);
					string managerId;

					getline(lineStream, managerId, '\t');

					if (chosenId == managerId)
					{

						string email, name, phone, ic, address;
						// Read each cell (column) from the line
						this->managerId = managerId;
						getline(lineStream, this->email, '\t');
						getline(lineStream, this->name, '\t');
						getline(lineStream, this->phone, '\t');
						getline(lineStream, this->ic, '\t');
						getline(lineStream, this->address, '\t');
						managerFile.close();

						getUserData();
						return;
					}
				}
				managerFile.clear(); // Clear any existing flags
				managerFile.seekg(0, ios::beg); // Move cursor to the beginning of the file
				cout << "\nInvalid Manager ID. Please try again." << endl;
			}
		}

	}

	void editManager()
	{
		string edit = "";

		do
		{
			cout << ".~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~." << endl;
			cout << "|                          MANAGER DETAILS                          |" << endl;
			cout << ".~~~~~~~~~~~~~~~~~~.~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~." << endl;
			cout << "| 1. User ID       | " << setw(46) << left << this->userId << " |" << endl;
			cout << "| 2. Manager ID    | " << setw(46) << left << this->managerId << " |" << endl;
			cout << "| 3. Name          | " << setw(46) << left << this->name << " |" << endl;
			cout << "| 4. Email Address | " << setw(46) << left << this->email << " |" << endl;
			cout << "| 5. Phone Number  | " << setw(46) << left << this->phone << " |" << endl;
			cout << "| 6. IC/Passport   | " << setw(46) << left << this->ic << " |" << endl;
			cout << "| 7. Address       | " << setw(46) << left << this->address << " |" << endl;
			cout << "| 8. Reset Password " << setw(46) << left << "" << "  |" << endl;
			cout << ".~~~~~~~~~~~~~~~~~~.~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~." << endl;


			cout << "\nWhich data do you want to edit? : ";

			string option = "";
			cin >> option;

			//Clear Buffer
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');

			//Get the update from user
			if (option == "1")
				cout << "User ID is not editable" << endl;
			else if (option == "2")
				cout << "Manager ID is not editable" << endl;
			else if (option == "3")
				this->setName();
			else if (option == "4")
				this->setNewEmail();
			else if (option == "5")
				this->setPhone();
			else if (option == "6")
				this->setIc();
			else if (option == "7")
				this->setAddress();
			else if (option == "8")
			{
				do
				{
					this->setNewPassword();
				} while (!this->confirmPass());
			}
			else
				cout << "\nInvalid input. Try again" << endl;

			cout << "\nDo you want to continue editing? [Y/N]: ";
			cin >> edit;

			//Clear Buffer
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');

			for (int i = 0; i < edit.length(); i++)
				edit[i] = tolower(edit[i]);
			this->updateManager();
			this->updateUser();
		} while (edit == "y" or edit == "yes");
	}

	void editPersonalDetails()
	{
		string edit = "";

		do
		{
			cout << ".~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~." << endl;
			cout << "|                        PERSONAL DETAILS                           |" << endl;
			cout << ".~~~~~~~~~~~~~~~~~~.~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~." << endl;
			cout << "| 1. Name          | " << setw(46) << left << this->name << " |" << endl;
			cout << "| 2. Email Address | " << setw(46) << left << this->email << " |" << endl;
			cout << "| 3. Phone Number  | " << setw(46) << left << this->phone << " |" << endl;
			cout << "| 4. IC/Passport   | " << setw(46) << left << this->ic << " |" << endl;
			cout << "| 5. Address       | " << setw(46) << left << this->address << " |" << endl;
			cout << "| 6. ResetPassword   " << setw(46) << left << "" << " |" << endl;
			cout << ".~~~~~~~~~~~~~~~~~~.~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~." << endl;

			cout << "Which data do you want to edit? : ";

			string option = "";
			cin >> option;

			//Clear Buffer
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');

			//Get the update from user
			if (option == "1")
				this->setName();
			else if (option == "2")
				this->setNewEmail();
			else if (option == "3")
				this->setPhone();
			else if (option == "4")
				this->setIc();
			else if (option == "5")
				this->setAddress();
			else if (option == "6")
			{
					this->setPassword();
					if (this->verifyPassword())
					{
						do
						{
							this->setNewPassword();
						} while (!this->confirmPass());
					}
					else
						cout << "\nPassword did not match." << endl;
				
			}	
			else
			cout << "\nInvalid input. Try again" << endl;
				

			cout << "\nDo you want to continue editing? [Y/N]: ";
			cin >> edit;

			//Clear Buffer
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');

			for (int i = 0; i < edit.length(); i++)
				edit[i] = tolower(edit[i]);
			this->updateManager();
			this->updateUser();
			
		 }while (edit == "y" or edit == "yes");
	 
    
}


	void searchManager(string search)
	{
		string line;
		ifstream managerFile("files/Managers.txt");

		//converting search key to lower case
		for (int i = 0; i < search.length(); i++)
			search[i] = tolower(search[i]);

		if (managerFile.is_open())
		{
			cout << endl;
			int managerCount = 0;

			// Read the lines from file
			getline(managerFile, line);
			cout << ".~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~." << endl;
			cout << "|                                                                      MANAGERS                                                                       |" << endl;
			cout << ".~~~~~~~~~~~~.~~~~~~~~~~~~~~~~~~~~~~~~.~~~~~~~~~~~~~~~~~~~~~~~~.~~~~~~~~~~~~~~~~~~.~~~~~~~~~~~~~~~~~~.~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~." << endl;
			cout << "| Manager ID | Email Address          | Name                   | Phone Number     | IC/Passport      | Address                                        |" << endl;
			cout << ".~~~~~~~~~~~~.~~~~~~~~~~~~~~~~~~~~~~~~.~~~~~~~~~~~~~~~~~~~~~~~~.~~~~~~~~~~~~~~~~~~.~~~~~~~~~~~~~~~~~~.~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~." << endl;
			while (getline(managerFile, line))
			{
				stringstream lineStream(line);

				string managerId, email, name, phone, ic, address;
				// Read each cell (column) from the line
				getline(lineStream, managerId, '\t');
				getline(lineStream, email, '\t');
				getline(lineStream, name, '\t');
				getline(lineStream, phone, '\t');
				getline(lineStream, ic, '\t');
				getline(lineStream, address, '\t');

				for (int i = 0; i < line.length(); i++)
					line[i] = tolower(line[i]);

				if (line.find(search) != string::npos or managerId == "Manager ID")
				{
					

					cout << "|    " << managerId
						<< "    | " << setw(22) << left << email
						<< " | " << setw(22) << left << name
						<< " | " << setw(16) << left << phone
						<< " | " << setw(16) << left << ic
						<< " | " << setw(46) << left << address << " |" << endl;

					managerCount++;
				}
			}
			cout << ".~~~~~~~~~~~~.~~~~~~~~~~~~~~~~~~~~~~~~.~~~~~~~~~~~~~~~~~~~~~~~~.~~~~~~~~~~~~~~~~~~.~~~~~~~~~~~~~~~~~~.~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~." << endl;
			cout << endl << "\nTotal no. of managers found: " << managerCount << endl << endl;
			managerFile.close();
		}
	}
};

class Order
{
public:
	string orderId;
	string productId;
	string customerId;
	int qty;
	string status;
	float itemPrice;
	float packagingPrice;

	Order()
	{

	}

	Order(string customerId)
	{
		this->customerId = customerId;
	}

	Order(string productId, string customerId)
	{
		this->productId = productId;
		this->customerId = customerId;
	}

	void setQty()
	{
		Product product(this->productId);
		while (true)
		{
			cout << "\nEnter quantity of product: ";

			string qtyInput;
			getline(cin, qtyInput);
			qtyInput.erase(std::remove(qtyInput.begin(), qtyInput.end(), '\t'), qtyInput.end());
			try
			{
				this->qty = stoi(qtyInput);
				if (0 <= this->qty and this->qty <= product.qty)
				{
					break;
				}
			}
			catch (invalid_argument&)
			{
				// Do nothing, just continue the loop
			}

			cout << "\nInvalid quantity or not sufficient product in stock." << endl;
		}
	}

	bool addOrder()
	{

		// Check if the product is already in the cart
		ifstream orderFile("files/Orders.txt");
		string line;
		getline(orderFile, line); // skip the first line
		while (getline(orderFile, line))
		{

			stringstream lineStream(line);
			string orderId, productId, productName, customerId, status, qtyString;
			int qty;
			getline(lineStream, orderId, '\t');
			getline(lineStream, productId, '\t');
			getline(lineStream, productName, '\t');
			getline(lineStream, customerId, '\t');
			getline(lineStream, qtyString, '\t');
			qty = stoi(qtyString);
			getline(lineStream, status, '\t');
			if (customerId == this->customerId && productId == this->productId && status == "Cart")
			{
				this->orderId = orderId;

				// Update the existing order
				this->qty += qty;

				// Open the file for writing
				ofstream tempOrderFile("files/tempOrders.txt");

				orderFile.clear(); // Clear any existing flags
				orderFile.seekg(0, ios::beg); // Move cursor to the beginning of the file

				//orderFile.open("files/orders.txt", ios::in);

				getline(orderFile, line);
				tempOrderFile << line << endl;
				while (getline(orderFile, line))
				{

					stringstream lineStream(line);

					getline(lineStream, orderId, '\t');
					getline(lineStream, productId, '\t');
					getline(lineStream, customerId, '\t');
					getline(lineStream, qtyString, '\t');
					qty = stoi(qtyString);
					getline(lineStream, status, '\t');

					if (orderId == this->orderId)
					{
						this->status = "Cart";

						
						tempOrderFile << this->orderId << "\t" << this->productId << "\t" << productName 
							<< "\t" << this->customerId << "\t" << this->qty << "\t" << this->status << endl;
					}
					else
					{
						// Write the original data to the temp file
						tempOrderFile << line << endl;
					}
				}
				// Close the original file and the temp file
				orderFile.close();
				tempOrderFile.close();

				// Remove the original file
				remove("files/Orders.txt");

				// Rename the temp file to the original file name
				rename("files/tempOrders.txt", "files/Orders.txt");
				return true;
			}

		}


		this->orderId = generateId("files/Orders.txt");
		this->status = "Cart";

		if (this->qty == 0)
			return false;

		Product product(this->productId);

		ofstream orderFileOut("files/Orders.txt", ios::app);
		if (orderFile.is_open())
		{
			orderFileOut << this->orderId << "\t" << this->productId << "\t" << product.name << "\t" 
				<< this->customerId << "\t" << this->qty << "\t" << this->status << endl;
			orderFileOut.close();
			return true;
		}
		//If everything goes well return true
		return false;
	}

	int countItems(string type)
	{
		string line, customerId, status;
		ifstream orderFile("files/Orders.txt");

		//Read the first line
		getline(orderFile, line);

		int itemCount = 0;

		if (orderFile.is_open())
		{
			// Get the number of items
			while (getline(orderFile, line))
			{
				stringstream lineStream(line);
				getline(lineStream, customerId, '\t');
				getline(lineStream, customerId, '\t');
				getline(lineStream, customerId, '\t');
				getline(lineStream, customerId, '\t');
				getline(lineStream, status, '\t');
				getline(lineStream, status, '\t');
				if (customerId == this->customerId and status.find(type) != std::string::npos)
					itemCount++;

			}
			orderFile.close();
		}

		return itemCount;
	}

	void showCart()
	{
		float grandTotal = 0;
		string line;
		ifstream orderFile("files/Orders.txt");


		if (orderFile.is_open())
		{
			cout << ".~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~." << endl;
			cout << "|                                                     CART                                                     |" << endl;
			cout << ".~~~~~~~~~~.~~~~~~~~~~~~.~~~~~~~~~~~~~~~~~~~~~~~~~~.~~~~~~~~~~.~~~~~~~~~~~~~~.~~~~~~~~~~~~~~~~~.~~~~~~~~~~~~~~~." << endl;
			cout << "| Order ID | Product ID | Product Name             | Quantity | Item Price   | Packaging Price |  Total Price  |" << endl;
			cout << ".~~~~~~~~~~.~~~~~~~~~~~~.~~~~~~~~~~~~~~~~~~~~~~~~~~.~~~~~~~~~~.~~~~~~~~~~~~~~.~~~~~~~~~~~~~~~~~.~~~~~~~~~~~~~~~." << endl;
			int itemCount = 0;
			// Read the lines from file

			getline(orderFile, line); // skip header row

			while (getline(orderFile, line))
			{
				stringstream lineStream(line);
				string orderId, productId, productName, customerId, qtyString, status;
				// Read each cell (column) from the line
				getline(lineStream, orderId, '\t');
				getline(lineStream, productId, '\t');
				getline(lineStream, productName, '\t');
				getline(lineStream, customerId, '\t');
				getline(lineStream, qtyString, '\t');
				int qty = stoi(qtyString);
				getline(lineStream, status, '\t');

				if (customerId != this->customerId or status != "Cart")
					continue;

				Product product(productId);

				float total = qty * (product.itemPrice + product.packagingPrice);


				cout << "|   " << orderId << "   |    " << productId << "    | " << setw(24) << left << productName
					<< " | " << setw(5) << right << qty
					<< "    | RM" << setw(10) << right << fixed << setprecision(2) << product.itemPrice
					<< " |   RM" << setw(9) << right << fixed << setprecision(2) << product.packagingPrice
					<< "   | RM" << setw(11) << right << fixed << setprecision(2) << total << " |" << endl;

				grandTotal += total;

				itemCount++;
			}
			cout << ".~~~~~~~~~~.~~~~~~~~~~~~.~~~~~~~~~~~~~~~~~~~~~~~~~~.~~~~~~~~~~.~~~~~~~~~~~~~~.~~~~~~~~~~~~~~~~~.~~~~~~~~~~~~~~~." << endl;
			cout << "|Total Items in the Cart: " << itemCount << setw(53) << left << ""
				<< "Amount Payable: RM " << setw(11) << right << fixed << setprecision(2) << grandTotal << " |" << endl;
			cout << ".~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~." << endl;
			orderFile.close();
		}
	}

	void validateCart()
	{
		// Open the original file for reading
		ifstream orderFile("files/Orders.txt");

		// Create a temporary file for writing the updated data
		ofstream tempOrderFile("files/tempOrders.txt");

		// Read the lines from the original file
		string line;
		getline(orderFile, line); // Skip the first line
		tempOrderFile << line << endl;
		while (getline(orderFile, line))
		{
			stringstream lineStream(line);
			string orderId, productId, productName, customerId, status, qtyString;
			int qty;
			//float itemPrice, packagingPrice;

			// Read each cell (column) from the line
			getline(lineStream, orderId, '\t');
			getline(lineStream, productId, '\t');
			getline(lineStream, productName, '\t');
			getline(lineStream, customerId, '\t');
			getline(lineStream, qtyString, '\t');
			qty = stoi(qtyString);
			getline(lineStream, status, '\t');
			

			if (customerId == this->customerId && status == "Cart")
			{

				// Create a Product object for the current product
				Product product(productId);
				if (product.qty >= qty)
				{
					// Write the line to the temp file
					
					tempOrderFile << line << endl;
				}
				else
				{
					if (product.qty == 0)
					{
						if (product.name == "")
						{
							// Print a message saying the product has been removed
							cout << "Product with ID: " << productId << " and name: " << productName 
								<< " is unavailable." << endl;
						}
						else
						{
							// Print a message saying the product has been removed due to out of stock
							cout << "Product with ID: " << productId << " and name: " << product.name 
								<< " is out of stock at the moment." << endl;
						}

					}
					else
					{
						// Print a message saying the quantity has been updated
						cout << "Quantity of product with ID: " << productId << " and name: " << product.name 
							<< " has been updated from " << qty << " to " << product.qty << " due to shortage in inventory." << endl;

						// Update the quantity to the quantity in stock
						qty = product.qty;

						// Write the updated data to the temp file
						tempOrderFile << orderId << "\t" << productId << "\t" << productName << "\t" << customerId 
							<< "\t" << qty << "\t" << status << endl;
					}
				}
			}
			else
			{
				// If the customerId from the file doesn't match the current Customer object's customerId, 
				// write the original data to the temp file			
				tempOrderFile << line << endl;
			}
		}

		// Close the original file and the temp file
		orderFile.close();
		tempOrderFile.close();

		// Remove the original file
		remove("files/Orders.txt");

		// Rename the temp file to the original file name
		rename("files/tempOrders.txt", "files/Orders.txt");
	}

	void chooseCartItem()
	{
		string line, chosenId;
		ifstream orderFile("files/Orders.txt");

		while (true)
		{

			cout << "\nEnter Order ID: ";
			cin >> chosenId;
			chosenId.erase(std::remove(chosenId.begin(), chosenId.end(), '\t'), chosenId.end());
			//Clear Buffer
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');

			if (orderFile.is_open())
			{

				getline(orderFile, line); //Skip the header row

				while (getline(orderFile, line))
				{
					stringstream lineStream(line);
					string orderId, productId, productName, customerId, qtyString, status;;
					int qty;

					getline(lineStream, orderId, '\t');
					getline(lineStream, productId, '\t');
					getline(lineStream, productName, '\t');
					getline(lineStream, customerId, '\t');
					getline(lineStream, qtyString, '\t');
					getline(lineStream, status, '\t');

					if (chosenId == orderId && this->customerId == customerId && status == "Cart")
					{

						// Read each cell (column) from the line
						this->orderId = orderId;
						this->productId = productId;
						this->customerId = customerId;
						this->qty = stoi(qtyString);
						this->status = status;
						orderFile.close();
						return;
					}
				}
				orderFile.clear(); // Clear any existing flags
				orderFile.seekg(0, ios::beg); // Move cursor to the beginning of the file
				cout << "\nInvalid Order ID. Please try again." << endl;
			}
		}
	}

	void editCartQty()
	{
		Product product(this->productId);

		cout << ".~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~." << endl;
		cout << "|                   ORDER DETAILS                 |" << endl;
		cout << ".~~~~~~~~~~~~~~~~~~~~~~~~.~~~~~~~~~~~~~~~~~~~~~~~~." << endl;
		cout << "| Order ID               | " << setw(22) << left << this->orderId << " |" << endl;
		cout << "| Product ID             | " << setw(22) << left << this->productId << " |" << endl;
		cout << "| Product Name           | " << setw(22) << left << product.name << " |" << endl;
		cout << "| Current Quantity       | " << setw(22) << left << this->qty << " |" << endl;
		cout << "| Amount in Stock        | " << setw(22) << left << product.qty << " |" << endl;
		cout << "| Item Price             | RM " << setw(19) << left << fixed << setprecision(2) 
			<< product.itemPrice << " |" << endl;
		cout << "| Packaging Price        | RM " << setw(19) << left << fixed << setprecision(2) 
			<< product.packagingPrice << " |" << endl;
		cout << "| Total Price per Unit   | RM " << setw(19) << left << fixed << setprecision(2) 
			<< product.itemPrice + product.packagingPrice << " |" << endl;
		cout << "| Current Total Price    | RM " << setw(19) << left << fixed << setprecision(2) 
			<< this->qty * (product.itemPrice + product.packagingPrice) << " |" << endl;
		cout << ".~~~~~~~~~~~~~~~~~~~~~~~~.~~~~~~~~~~~~~~~~~~~~~~~~." << endl;

		cout << "\nYou can now update the quantity of product here:" << endl;

		this->setQty();
	}

	void updateCart()
	{
		// Open the original file for reading
		ifstream orderFile("files/Orders.txt");

		// check if file is open
		if (!orderFile.is_open())
		{
			cout << "Something went wrong. Update Failed." << endl;
			return;
		}

		// Create a temporary file for writing the updated data
		ofstream tempOrderFile("files/tempOrders.txt");

		// check if file is open
		if (!tempOrderFile.is_open())
		{
			cout << "Something went wrong. Update Failed." << endl;
			orderFile.close();
			return;
		}
		// Read the lines from the original file
		string line;

		getline(orderFile, line); // skip the header row
		tempOrderFile << line << endl;
		while (getline(orderFile, line))
		{
			stringstream lineStream(line);
			string orderId, productId, productName, customerId, status, qtyString;
			int qty;
			getline(lineStream, orderId, '\t');
			getline(lineStream, productId, '\t');
			getline(lineStream, productName, '\t');
			getline(lineStream, customerId, '\t');
			getline(lineStream, qtyString, '\t');
			qty = stoi(qtyString);
			getline(lineStream, status, '\t');

			// Check if the userId from the file matches the userId of the current User object
			if (orderId == this->orderId and this->qty > 0)
			{
				// If it matches, write the updated data to the temp file
				tempOrderFile << this->orderId << "\t" << this->productId << "\t" << productName 
					<< "\t" << this->customerId << "\t" << this->qty << "\t" << this->status << endl;
			}
			else if (orderId == this->orderId and this->qty == 0)
			{
				//skip
			}
			else
			{
				// If it doesn't match, write the original data to the temp file
				tempOrderFile << line << endl;
			}
		}

		// Close the original file and the temp file
		orderFile.close();
		tempOrderFile.close();

		// Remove the original file
		if (remove("files/Orders.txt") != 0)
		{
			cout << "Something went wrong. Update Failed." << endl;
			return;
		}

		// Rename the temp file to the original file name
		if (rename("files/tempOrders.txt", "files/Orders.txt") != 0)
		{
			cout << "Something went wrong. Update Failed." << endl;
			return;
		}
		if (this->qty == 0)
		{
			cout << "\nProduct has been deleted from cart." << endl;
		}
		else
		{
			cout << "\nCart updated!." << endl;
		}

		return;
	}

	void deleteCartItem()
	{
		// Open the original file for reading
		ifstream orderFile("files/Orders.txt");

		// check if file is open
		if (!orderFile.is_open())
		{
			cout << "Something went wrong. Deleting Process Failed." << endl;
			return;
		}

		// Create a temporary file for writing the updated data
		ofstream tempOrderFile("files/tempOrders.txt");

		// check if file is open
		if (!tempOrderFile.is_open())
		{
			cout << "Something went wrong. Deleting Process Failed." << endl;
			orderFile.close();
			return;
		}

		// Read the lines from the original file
		string line;

		getline(orderFile, line); // skip the header row
		tempOrderFile << line << endl;
		while (getline(orderFile, line))
		{
			stringstream lineStream(line);
			string orderId;
			getline(lineStream, orderId, '\t');

			// Check if the userId from the file matches the userId of the current User object
			if (orderId != this->orderId)
			{
				// If it doesn't match, write the original data to the temp file
				tempOrderFile << line << endl;
			}
		}

		// Close the original file and the temp file
		orderFile.close();
		tempOrderFile.close();

		// Remove the original file
		if (remove("files/orders.txt") != 0)
		{
			cout << "Something went wrong. Deleting Process Failed." << endl;
			return;
		}

		// Rename the temp file to the original file name
		if (rename("files/tempOrders.txt", "files/Orders.txt") != 0)
		{
			cout << "Something went wrong. Deleting Process Failed." << endl;
			return;
		}
		cout << "\nProduct has been deleted from cart." << endl;
		return;
	}

	void Bill()
	{
		float grandTotal = 0;
		string line;
		ifstream orderFile("files/Orders.txt");

		Customer customer(this->customerId);

		cout << ".~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~." << endl;
		cout << "|                                          BILL                                           |" << endl;
		cout << ".~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~." << endl;
		cout << "| Customer ID: " << setw(75) << left << this->customerId << "|" << endl;
		cout << "| Customer Name: " << setw(73) << left << customer.name << "|" << endl;
		cout << "| Customer Phone Number: " << setw(65) << left << customer.phone << "|" << endl;
		cout << "| Customer Address: " << setw(70) << left << customer.address << "|" << endl;
		cout << ".~~~~~~~~~~~~~~~~~~~~~~~~~~~~~.~~~~~~~~~~~~~~.~~~~~~~~~~~~~~~~~.~~~~~~~~~~.~~~~~~~~~~~~~~~." << endl;
		cout << "| Product Name                |  Item Price  | Packaging Price | Quantity |  Total Price  |" << endl;
		cout << ".~~~~~~~~~~~~~~~~~~~~~~~~~~~~~.~~~~~~~~~~~~~~.~~~~~~~~~~~~~~~~~.~~~~~~~~~~.~~~~~~~~~~~~~~~." << endl;
		if (orderFile.is_open())
		{
			int itemCount = 0;
			// Read the lines from file

			getline(orderFile, line); // skip the first row
			while (getline(orderFile, line))
			{
				stringstream lineStream(line);
				string orderId, productId, productName, customerId, qtyString, status;
				// Read each cell (column) from the line
				getline(lineStream, orderId, '\t');
				getline(lineStream, productId, '\t');
				getline(lineStream, productName, '\t');
				getline(lineStream, customerId, '\t');
				getline(lineStream, qtyString, '\t');
				int qty = stoi(qtyString);
				getline(lineStream, status, '\t');

				if (customerId != this->customerId or status != "Cart")
					continue;

				Product product(productId);

				float total = qty * (product.itemPrice + product.packagingPrice);
				cout << "| " << setw(24) << left << productName
					<< "    | RM" << setw(10) << right << fixed << setprecision(2) << product.itemPrice
					<< " |   RM" << setw(9) << right << fixed << setprecision(2) << product.packagingPrice
					<< "   | " << setw(5) << right << qty
					<< "    | RM" << setw(11) << right << fixed << setprecision(2) << total << " |" << endl;

				grandTotal += qty * (product.itemPrice + product.packagingPrice);

				itemCount++;


			}
			cout << ".~~~~~~~~~~~~~~~~~~~~~~~~~~~~~.~~~~~~~~~~~~~~.~~~~~~~~~~~~~~~~~.~~~~~~~~~~.~~~~~~~~~~~~~~~." << endl;
			cout << "| Total Products: " << itemCount << setw(40) << left << ""
				<< "Amount Payable: RM " << setw(11) << right << fixed << setprecision(2) << grandTotal << " |" << endl;
			cout << ".~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~." << endl;
			orderFile.close();
		}
	}

	void Pay(string paymentMethod)
	{
		//Payment Method: card or cod
		if (paymentMethod == "Card")
		{
			string cardNumber, expiryDate, cvv;

			while (true)
			{
				cout << "\nEnter Card Number: ";
				cin >> cardNumber;
				//Clear Buffer
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');

				try
				{
					int nDigits = cardNumber.length();
					int nSum = 0, isSecond = false;
					for (int i = nDigits - 1; i >= 0; i--)
					{
						int d = cardNumber[i] - '0';
						if (isSecond == true)
							d = d * 2;
						nSum += d / 10;
						nSum += d % 10;
						isSecond = !isSecond;
					}
					if (nSum % 10 == 0)
						break;
					else
						cout << "\nInvalid input. Enter a valid card number." << endl;
				}
				catch (exception e)
				{
					cout << "\nInvalid input" << endl;
				}

			}

			while (true)
			{
				cout << "\nEnter Expiry Date [MM/YY]: ";
				cin >> cardNumber;
				//Clear Buffer
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');

				if (cardNumber != "")
				{
					break;
				}
				else
				{
					cout << "\nExpiry Date cannot be empty." << endl;
				}

			}

			while (true)
			{
				cout << "\nEnter CVV: ";
				cin >> cvv;
				//Clear Buffer
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');

				if (cvv != "")
				{
					break;
				}
				else
				{
					cout << "\nCVV cannot be empty." << endl;
				}

			}
		}


		// Open the original file for reading
		ifstream orderFile("files/Orders.txt");

		// check if file is open
		if (!orderFile.is_open())
		{
			cout << "Something went wrong. Payment Failed." << endl;
			return;
		}

		// Create a temporary file for writing the updated data
		ofstream tempOrderFile("files/tempOrders.txt");

		// check if file is open
		if (!tempOrderFile.is_open())
		{
			cout << "Something went wrong. Payment Failed." << endl;
			orderFile.close();
			return;
		}
		// Read the lines from the original file
		string lineOrder, lineProduct;

		getline(orderFile, lineOrder); // skip the header row
		tempOrderFile << lineOrder << endl;
		while (getline(orderFile, lineOrder))
		{
			stringstream lineStreamOrder(lineOrder);
			string orderId, productId, productName, customerId, status, qtyString;
			getline(lineStreamOrder, orderId, '\t');
			getline(lineStreamOrder, productId, '\t');
			getline(lineStreamOrder, productName, '\t');
			getline(lineStreamOrder, customerId, '\t');
			getline(lineStreamOrder, qtyString, '\t');
			int qty = stoi(qtyString);
			getline(lineStreamOrder, status, '\t');

			// Check if the userId from the file matches the userId of the current User object
			if (customerId == this->customerId and status == "Cart")
			{
				Product product(productId);
				// If it matches, write the updated data to the temp file
				tempOrderFile << orderId << "\t" << productId << "\t" << productName << "\t" << customerId << "\t"
					<< qty << "\t" << paymentMethod << "\t"
					<< fixed << setprecision(2) << product.itemPrice << "\t" << fixed << setprecision(2) 
					<< product.packagingPrice << "\t" << fixed << setprecision(2) 
					<< qty * (product.itemPrice + product.packagingPrice) << endl;

				// Open the original file for reading
				ifstream productFile("files/Products.txt");

				// check if file is open
				if (!productFile.is_open())
				{
					cout << "Something went wrong. Payment Failed." << endl;
					return;
				}

				// Create a temporary file for writing the updated data
				ofstream tempProductFile("files/tempProducts.txt");

				// check if file is open
				if (!tempProductFile.is_open())
				{
					cout << "Something went wrong. Payment Failed." << endl;
					productFile.close();
					return;
				}

				while (getline(productFile, lineProduct))
				{
					stringstream lineStreamProduct(lineProduct);
					string productId2;
					// Read each cell (column) from the line
					getline(lineStreamProduct, productId2, '\t');


					// Check if the userId from the file matches the userId of the current User object
					if (productId2 == productId)
					{
						// If it matches, write the updated data to the temp file
						tempProductFile << productId2 << "\t" << product.name << "\t" << product.categoryId
							<< "\t" << fixed << setprecision(2) << product.itemPrice << "\t" << fixed 
							<< setprecision(2) << product.packagingPrice << "\t" << product.qty - qty 
							<< "\t" << product.details << endl;

					}
					else
					{
						// If it doesn't match, write the original data to the temp file
						tempProductFile << lineProduct << endl;
					}
				}

				// Close the original file and the temp file
				productFile.close();
				tempProductFile.close();

				// Remove the original file
				if (remove("files/Products.txt") != 0)
				{
					cout << "Something went wrong. Payment Failed." << endl;
					return;
				}

				// Rename the temp file to the original file name
				if (rename("files/tempProducts.txt", "files/Products.txt") != 0)
				{
					cout << "Something went wrong. Payment Failed." << endl;
					return;
				}
			}
			else
			{
				// If it doesn't match, write the original data to the temp file
				tempOrderFile << lineOrder << endl;
			}
		}

		// Close the original file and the temp file
		orderFile.close();
		tempOrderFile.close();



		// Remove the original file
		if (remove("files/Orders.txt") != 0)
		{
			cout << "Something went wrong. Payment Failed." << endl;
			return;
		}

		// Rename the temp file to the original file name
		if (rename("files/tempOrders.txt", "files/Orders.txt") != 0)
		{
			cout << "Something went wrong. Payment Failed." << endl;
			return;
		}



		if (paymentMethod == "Card")
			cout << "\nYour payment was successful. Order has been confirmed." << endl;
		else if (paymentMethod == "COD")
			cout << "\nOrder has been confirmed. Payment Method: Cash On Delivery." << endl;
	}

	void showAllOrders()
	{
		string line;
		ifstream orderFile("files/Orders.txt");

		cout << ".~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~." << endl;
		cout << "|                                                               ORDERS                                                                |" << endl;
		cout << ".~~~~~~~~~~.~~~~~~~~~~~~~.~~~~~~~~~~~~.~~~~~~~~~~~~~~~~~~~~~~~~~~.~~~~~~~~.~~~~~~~~~~.~~~~~~~~~~~~~~.~~~~~~~~~~~~~~~~~.~~~~~~~~~~~~~~~." << endl;
		cout << "| Order ID | Customer ID | Product ID |       Product Name       | Status | Quantity |  Item Price  | Packaging Price |  Total Price  |" << endl;
		cout << ".~~~~~~~~~~.~~~~~~~~~~~~~.~~~~~~~~~~~~.~~~~~~~~~~~~~~~~~~~~~~~~~~.~~~~~~~~.~~~~~~~~~~.~~~~~~~~~~~~~~.~~~~~~~~~~~~~~~~~.~~~~~~~~~~~~~~~." << endl;
		if (orderFile.is_open())
		{
			int itemCount = 0;
			// Read the lines from file
			getline(orderFile, line); // skip the first row
			while (getline(orderFile, line))
			{
				stringstream lineStream(line);
				string orderId, productId, productName, customerId, qtyString, status, itemPrice, packagingPrice, totalPrice;
				// Read each cell (column) from the line
				getline(lineStream, orderId, '\t');
				getline(lineStream, productId, '\t');
				getline(lineStream, productName, '\t');
				getline(lineStream, customerId, '\t');
				getline(lineStream, qtyString, '\t');
				getline(lineStream, status, '\t');
				getline(lineStream, itemPrice, '\t');
				getline(lineStream, packagingPrice, '\t');
				getline(lineStream, totalPrice, '\t');

				if (status == "Cart")
				{
					Product product(productId);

					int qty = stoi(qtyString);
					float total = qty * (product.itemPrice + product.packagingPrice);

					cout << "|   " << orderId << "   |    " << customerId << "     |    " << productId << "    | " << setw(24) << left << productName
						<< " |  " << setw(5) << left << status
						<< " | " << setw(5) << right << qtyString
						<< "    | RM" << setw(10) << right << fixed << setprecision(2) << product.itemPrice
						<< " |   RM" << setw(9) << right << fixed << setprecision(2) << product.packagingPrice
						<< "   | RM" << setw(11) << right << fixed << setprecision(2) << total << " |" << endl;
					itemCount++;
				}
				if ((status == "Card" or status == "COD"))
				{
	
					cout << "|   " << orderId << "   |    " << customerId << "     |    " << productId << "    | " << setw(24) << left << productName
						<< " |  " << setw(5) << left << status
						<< " | " << setw(5) << right << qtyString
						<< "    | RM" << setw(10) << right << itemPrice
						<< " |   RM" << setw(9) << right << packagingPrice
						<< "   | RM" << setw(11) << right << totalPrice << " |" << endl;

					itemCount++;
				}
			}
			cout << ".~~~~~~~~~~.~~~~~~~~~~~~~.~~~~~~~~~~~~.~~~~~~~~~~~~~~~~~~~~~~~~~~.~~~~~~~~.~~~~~~~~~~.~~~~~~~~~~~~~~.~~~~~~~~~~~~~~~~~.~~~~~~~~~~~~~~~." << endl;
			cout << endl << "\nTotalno. of products: " << itemCount << endl << endl;
			orderFile.close();
		}
	}

	void showOrdersByCustomer()
	{
		string line;
		ifstream orderFile("files/Orders.txt");

		cout << ".~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~." << endl;
		cout << "|                                                        ORDERS                                                         |" << endl;
		cout << ".~~~~~~~~~~.~~~~~~~~~~~~.~~~~~~~~~~~~~~~~~~~~~~~~~~.~~~~~~~~.~~~~~~~~~~.~~~~~~~~~~~~~~.~~~~~~~~~~~~~~~~~.~~~~~~~~~~~~~~~." << endl;
		cout << "| Order ID | Product ID | Product Name             | Status | Quantity |  Item Price  | Packaging Price |  Total Price  |" << endl;
		cout << ".~~~~~~~~~~.~~~~~~~~~~~~.~~~~~~~~~~~~~~~~~~~~~~~~~~.~~~~~~~~.~~~~~~~~~~.~~~~~~~~~~~~~~.~~~~~~~~~~~~~~~~~.~~~~~~~~~~~~~~~." << endl;
		if (orderFile.is_open())
		{
			int itemCount = 0;
			// Read the lines from file
			getline(orderFile, line); // skip the first row
			while (getline(orderFile, line))
			{
				stringstream lineStream(line);
				string orderId, productId, productName, customerId, qtyString, status, itemPrice, packagingPrice, totalPrice;
				// Read each cell (column) from the line
				getline(lineStream, orderId, '\t');
				getline(lineStream, productId, '\t');
				getline(lineStream, productName, '\t');
				getline(lineStream, customerId, '\t');
				getline(lineStream, qtyString, '\t');
				getline(lineStream, status, '\t');
				getline(lineStream, itemPrice, '\t');
				getline(lineStream, packagingPrice, '\t');
				getline(lineStream, totalPrice, '\t');

				if (customerId != this->customerId)
					continue;


				if ((status == "Card" or status == "COD"))
				{

					cout << "|   " << orderId << "   |    " << productId << "    | " << setw(24) << left << productName
						<< " |  " << setw(5) << left << status
						<< " | " << setw(5) << right << qtyString
						<< "    | RM" << setw(10) << right << itemPrice
						<< " |   RM" << setw(9) << right << packagingPrice
						<< "   | RM" << setw(11) << right << totalPrice << " |" << endl;
					itemCount++;

				}



			}
			cout << ".~~~~~~~~~~.~~~~~~~~~~~~.~~~~~~~~~~~~~~~~~~~~~~~~~~.~~~~~~~~.~~~~~~~~~~.~~~~~~~~~~~~~~.~~~~~~~~~~~~~~~~~.~~~~~~~~~~~~~~~." << endl;
			cout << endl << "\nTotal no. of products: " << itemCount << endl << endl;
			orderFile.close();
		}
	}

	void showOrderHistory()
	{
		string line;
		ifstream orderFile("files/Orders.txt");

		cout << ".~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~." << endl;
		cout << "|                                                     ORDER HISTORY                                                     |" << endl;
		cout << ".~~~~~~~~~~.~~~~~~~~~~--.~~~~~~~~~~~~~~~~~~~~~~~~~-.~~~~~---.~~~~~~~~~~.~~~~~~~~~~~~~~.~~~~~~~~~~~~~~~~~.~~~~~~~~~~~~~~~." << endl;
		cout << "| Order ID | Product ID | Product Name             | Status | Quantity |  Item Price  | Packaging Price |  Total Price  |" << endl;
		cout << ".~~~~~~~~~~.~~~~~~~~~~~~.~~~~~~~~~~~~~~~~~~~~~~~~~~.~~~~~~~~.~~~~~~~~~~.~~~~~~~~~~~~~~.~~~~~~~~~~~~~~~~~.~~~~~~~~~~~~~~~." << endl;
		if (orderFile.is_open())
		{
			int itemCount = 0;
			// Read the lines from file
			getline(orderFile, line); // skip the first row
			while (getline(orderFile, line))
			{
				stringstream lineStream(line);
				string orderId, productId, productName, customerId, qty, status, itemPrice, packagingPrice, totalPrice;
				// Read each cell (column) from the line
				getline(lineStream, orderId, '\t');
				getline(lineStream, productId, '\t');
				getline(lineStream, productName, '\t');
				getline(lineStream, customerId, '\t');
				getline(lineStream, qty, '\t');
				getline(lineStream, status, '\t');
				getline(lineStream, itemPrice, '\t');
				getline(lineStream, packagingPrice, '\t');
				getline(lineStream, totalPrice, '\t');

				if (customerId != this->customerId or (status != "Card" and status != "COD"))
					continue;

				Product product(productId);

				cout << "|   " << orderId << "   |    " << productId << "    | " << setw(24) << left << productName
					<< " |  " << setw(5) << left << status
					<< " | " << setw(5) << right << qty
					<< "    | RM" << setw(10) << right << itemPrice
					<< " |   RM" << setw(9) << right << packagingPrice
					<< "   | RM" << setw(11) << right << totalPrice << " |" << endl;

				itemCount++;


			}
			cout << ".~~~~~~~~~~.~~~~~~~~~~~~.~~~~~~~~~~~~~~~~~~~~~~~~~~.~~~~~~~~.~~~~~~~~~~.~~~~~~~~~~~~~~.~~~~~~~~~~~~~~~~~.~~~~~~~~~~~~~~~." << endl;
			cout << endl << "\nTotal no. of products: " << itemCount << endl << endl;
			orderFile.close();
		}
	}

	void searchOrder(string search)
	{
		for (int i = 0; i < search.length(); i++)
			search[i] = tolower(search[i]);

		string line;
		ifstream orderFile("files/Orders.txt");

		cout << ".~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~." << endl;
		cout << "|                                                               ORDERS                                                                |" << endl;
		cout << ".~~~~~~~~~~.~~~~~~~~~~~~~.~~~~~~~~~~~~.~~~~~~~~~~~~~~~~~~~~~~~~~~.~~~~~~~~.~~~~~~~~~~.~~~~~~~~~~~~~~.~~~~~~~~~~~~~~~~~.~~~~~~~~~~~~~~~." << endl;
		cout << "| Order ID | Customer ID | Product ID | Product Name             | Status | Quantity |  Item Price  | Packaging Price |  Total Price  |" << endl;
		cout << ".~~~~~~~~~~.~~~~~~~~~~~~~.~~~~~~~~~~~~.~~~~~~~~~~~~~~~~~~~~~~~~~~.~~~~~~~~.~~~~~~~~~~.~~~~~~~~~~~~~~.~~~~~~~~~~~~~~~~~.~~~~~~~~~~~~~~~." << endl;
		if (orderFile.is_open())
		{
			int itemCount = 0;
			// Read the lines from file
			getline(orderFile, line); // skip the first row
			while (getline(orderFile, line))
			{
				stringstream lineStream(line);
				string orderId, productId, productName, customerId, qtyString, status, itemPrice, packagingPrice, totalPrice;
				// Read each cell (column) from the line
				getline(lineStream, orderId, '\t');
				getline(lineStream, productId, '\t');
				getline(lineStream, productName, '\t');
				getline(lineStream, customerId, '\t');
				getline(lineStream, qtyString, '\t');
				getline(lineStream, status, '\t');
				getline(lineStream, itemPrice, '\t');
				getline(lineStream, packagingPrice, '\t');
				getline(lineStream, totalPrice, '\t');

				for (int i = 0; i < line.length(); i++)
					line[i] = tolower(line[i]);
				if (line.find(search) != string::npos or orderId == "Order ID")
				{

					if (status == "Cart")
					{
						Product product(productId);

						int qty = stoi(qtyString);
						float total = qty * (product.itemPrice + product.packagingPrice);

						cout << "|   " << orderId << "   |    " << customerId << "     |    " << productId << "    | " << setw(24) << left << productName
							<< " |  " << setw(5) << left << status
							<< " | " << setw(5) << right << qtyString
							<< "    | RM" << setw(10) << right << fixed << setprecision(2) << product.itemPrice
							<< " |   RM" << setw(9) << right << fixed << setprecision(2) << product.packagingPrice
							<< "   | RM" << setw(11) << right << fixed << setprecision(2) << total << " |" << endl;
						itemCount++;
					}
					if ((status == "Card" or status == "COD"))
					{
						cout << "|   " << orderId << "   |    " << customerId << "     |    " << productId << "    | " << setw(24) << left << productName
							<< " |  " << setw(5) << left << status
							<< " | " << setw(5) << right << qtyString
							<< "    | RM" << setw(10) << right << itemPrice
							<< " |   RM" << setw(9) << right << packagingPrice
							<< "   | RM" << setw(11) << right << totalPrice << " |" << endl;

						itemCount++;
					}
				}
			}
			cout << ".~~~~~~~~~~.~~~~~~~~~~~~~.~~~~~~~~~~~~.~~~~~~~~~~~~~~~~~~~~~~~~~~.~~~~~~~~.~~~~~~~~~~.~~~~~~~~~~~~~~.~~~~~~~~~~~~~~~~~.~~~~~~~~~~~~~~~." << endl;
			cout << endl << "\nTotal no. of products found: " << itemCount << endl << endl;
			orderFile.close();
		}
	}
};

void headers()
{
	string id = "0001";
	string name = "Zahra Tasnim";
	string email = "zahra@admin.com";
	string password = "Zahra@1709";
	string userType = "admin";

	struct _stat st;
	if (_stat("files", &st) != 0)
	{
		// Directory does not exist, create it
		_mkdir("files");
	}

	// Create the users.csv file if it does not exist
	ifstream userFile("files/Users.txt");
	if (!userFile.is_open())
	{
		ofstream userFile("files/Users.txt");
		if (userFile.is_open())
		{

			userFile << "User ID\tEmail\tPassword\tUser Type" << endl; 
			userFile << id << "\t" << email << "\t" << password << "\t" << userType << endl; 
			userFile.close();
		}
	}
	else
	{
		userFile.close();
	}

	// Create the admins.txt file if it does not exist
	ifstream adminFile("files/Admins.txt");
	if (!adminFile.is_open())
	{
		ofstream adminFile("files/Admins.txt");
		if (adminFile.is_open())
		{
			adminFile << "Admin ID\tEmail\t\tName" << endl;
			adminFile << id << "\t" << email << "\t" << name << endl;
			adminFile.close();
		}
	}
	else
	{
		adminFile.close();
	}

	// Create the customers.csv file if it does not exist
	ifstream customerFile("files/Customers.txt");
	if (!customerFile.is_open())
	{
		ofstream customerFile("files/Customers.txt");
		if (customerFile.is_open())
		{
			customerFile << "Customer ID" << "\t" << "Email" << "\t" << "Name" << "\t" << "Phone" << "\t" << "Address" << endl;
			customerFile.close();
		}
	}
	else
	{
		customerFile.close();
	}

	ifstream managerFile("files/Managers.txt");
	if (!managerFile.is_open())
	{
		ofstream managerFile("files/Managers.txt");
		if (managerFile.is_open())
		{
			managerFile << "Manager ID" << "\t" << "Email" << "\t" << "Name" << "\t" << "Phone" << "\t" << "IC/Passport Number" << "\t" << "Address" << endl;
			managerFile.close();
		}
	}
	else
	{
		managerFile.close();
	}

	// Create the categories.txt file if it does not exist
	ifstream categoryFile("files/Categories.txt");
	if (!categoryFile.is_open())
	{
		ofstream categoryFile("files/Categories.txt");
		if (categoryFile.is_open())
		{
			categoryFile << "Category ID" << "\t" << "Category Name" << endl;
			categoryFile << "0000" << "\t" << "Assorted" << endl;
			categoryFile.close();
		}
	}
	else
	{
		categoryFile.close();
	}

	// Create the categories.txt file if it does not exist
	ifstream productFile("files/Products.txt");
	if (!productFile.is_open())
	{
		ofstream productFile("files/Products.txt");
		if (productFile.is_open())
		{
			productFile << "Product ID\tName\t\tCategory ID\tItem Price\tPackaging Price\tQuantity\tDetails\n";
			productFile.close();
		}
	}
	else
	{
		productFile.close();
	}

	// Create the orders.txt file if it does not exist
	ifstream orderFile("files/Orders.txt");
	if (!orderFile.is_open())
	{
		ofstream orderFile("files/Orders.txt");
		if (orderFile.is_open())
		{
			orderFile << "Order ID\tProduct ID\tProduct Name\t\tCustomer ID\tQuantity\tStatus\tItem Price\tPackaging Price\tTotal Price\n";
			orderFile.close();
		}
	}
	else
	{
		orderFile.close();
	}

}

void adminMenu()
{
	string option;

	while (true)
	{
	    cout << "\t\tYou have logged in as admin." << endl;
	    cout << "\n\nADMIN MENU" << endl << endl << endl;
		cout << ".------------------------.-------------------------." << endl;
		cout << ".        MANAGERS        .       CUSTOMERS         ." << endl;
		cout << ".------------------------.-------------------------." << endl;
		cout << ". 1. Add Manager         . 6. Add Customer         ." << endl;
		cout << ". 2. View Managers       . 7. View Customers       ." << endl;
		cout << ". 3. Edit Manager        . 8. Edit Customer        ." << endl;
		cout << ". 4. Delete Manager      . 9. Delete Customer      ." << endl;
		cout << ". 5. Search Manager      . 10. Search Customer     ." << endl;
		cout << ".------------------------.-------------------------." << endl; 
		cout << ". 11. Change Admin Password                        ." << endl;
		cout << ". 0.  Logout                                       ." << endl;
		cout << ".------------------------.-------------------------." << endl;
		
		cout << "\nWhat would you like to do? : " << endl;
		cin >> option;

		//Clear Buffer
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');

		if (option == "1")	// Add Manager
		{
			Manager manager;

			manager.setName();

			// return if email already is in use
			if (manager.setNewEmail())
			{
				manager.setPhone();
				manager.setIc();

				//set password of manager, confirm and match it
				do
				{
					manager.setNewPassword();
				} while (!manager.confirmPass());

				manager.setAddress();

				if (manager.addUser() && manager.addManager())
					cout << "\nNew Manager has been added!" << endl;
				else
					cout << "Something went wrong." << endl;
			}
		}
		else if (option == "2")	// View managers
		{
			Manager manager;
			if (manager.countManager() == 0)
			{
				cout << "\nThis store does not have managers yet!." << endl;
			}
			else
			{
				manager.showAllManagers();
			}


		}
		else if (option == "3") // Edit Manager
		{
			Manager manager;
			if (manager.countManager() == 0)
			{
				cout << "\nThis store does not have managers yet!." << endl;
			}
			else
			{
				manager.showAllManagers();
				manager.chooseManager();
				// Edit Manager details in the program
				manager.editManager();

				// Update the manager details in the files
				if (manager.updateManager() and manager.updateUser())
					cout << "\nManager details have been updated." << endl;
				else
					cout << "Update failed." << endl;
			}
		}
		else if (option == "4") // Delete Manager
		{
			Manager manager;
			if (manager.countManager() == 0)
			{
				cout << "\nThis store does not have managers yet!." << endl;
			}
			else
			{
				manager.showAllManagers();
				manager.chooseManager();


				cout << ".~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~." << endl;
				cout << "|                         MANAGER DETAILS                           |" << endl;
				cout << ".~~~~~~~~~~~~~~~~~~.~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~." << endl;
				cout << "| 1. User ID       | " << setw(46) << left << manager.userId << " |" << endl;
				cout << "| 2. Manager ID    | " << setw(46) << left << manager.managerId << " |" << endl;
				cout << "| 3. Name          | " << setw(46) << left << manager.name << " |" << endl;
				cout << "| 4. Email Address | " << setw(46) << left << manager.email << " |" << endl;
				cout << "| 5. Phone Number  | " << setw(46) << left << manager.phone << " |" << endl;
				cout << "| 6. IC/Passport   | " << setw(46) << left << manager.ic << " |" << endl;
				cout << "| 7. Address       | " << setw(46) << left << manager.address << " |" << endl;
				cout << ".~~~~~~~~~~~~~~~~~~.~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~." << endl;

				cout << "Are you sure you want to delete this manager? [y/n]: ";

				string deleteConfirmation = "";
				cin >> deleteConfirmation;

				//Clear Buffer
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');

				for (int i = 0; i < deleteConfirmation.length(); i++)
					deleteConfirmation[i] = tolower(deleteConfirmation[i]);


				if (deleteConfirmation == "y" or deleteConfirmation == "yes")
				{
					if (manager.deleteManager() and manager.deleteUser())
						cout << "\nManager account has been deleted." << endl;
					else
						cout << "\nDeleting Process Failed." << endl;

				}
				else
				{
					cout << "\nManager account will not be deleted. Process cancelled." << endl;
				}
			}

		}
		else if (option == "5")
		{
			string search = "";
			cout << "\nEnter Search Keyword: ";
			getline(cin, search);

			Manager manager;

			manager.searchManager(search);

		}
		else if (option == "6") // Add Customer
		{
			Customer customer;

			customer.setName();

			// return if email already is in use
			if (customer.setNewEmail())
			{
				customer.setPhone();

				//set password of manager, confirm and match it
				do
				{
					customer.setNewPassword();
				} while (!customer.confirmPass());

				customer.setAddress();

				if (customer.addUser() && customer.addCustomer())
					cout << "\nNew customer added." << endl;
				else
					cout << "Something went wrong." << endl;
			}

		}
		else if (option == "7") // View Customers
		{
			Customer customer;
			if (customer.countCustomer() == 0)
			{
				cout << "\nThere are no regsitered customers." << endl;
			}
			else
			{
				customer.showAllCustomers();
			}
		}
		else if (option == "8") // Edit Customer
		{
			Customer customer;
			if (customer.countCustomer() == 0)
			{
				cout << "\nThere are no registered customers." << endl;
			}
			else
			{
				customer.showAllCustomers();
				customer.chooseCustomer();

				// Edit Customer details in the program
				customer.editCustomer();

				// Update the customer details in the files
				if (customer.updateCustomer() and customer.updateUser())
					cout << "\nCustomer details have been updated." << endl;
				else
					cout << "Something went wrong. Update Failed." << endl;
			}


		}
		else if (option == "9") // Delete Customer
		{
			Customer customer;
			if (customer.countCustomer() == 0)
			{
				cout << "\nThere are regsitered customers." << endl;
			}
			else
			{
				customer.showAllCustomers();
				customer.chooseCustomer();

				cout << ".~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~." << endl;
				cout << "|                       CUSTOMER DETAILS                            |" << endl;
				cout << ".~~~~~~~~~~~~~~~~~~.~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~." << endl;
				cout << "| 1. User ID       | " << setw(46) << left << customer.userId << " |" << endl;
				cout << "| 2. Customer ID   | " << setw(46) << left << customer.customerId << " |" << endl;
				cout << "| 3. Name          | " << setw(46) << left << customer.name << " |" << endl;
				cout << "| 4. Email Address | " << setw(46) << left << customer.email << " |" << endl;
				cout << "| 5. Phone Number  | " << setw(46) << left << customer.phone << " |" << endl;
				cout << "| 6. Address       | " << setw(46) << left << customer.address << " |" << endl;
				cout << "| 7. Change Password " << setw(46) << left << "" << "  |" << endl;
				cout << ".~~~~~~~~~~~~~~~~~~.~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~." << endl;

				cout << "Are you sure you want to delete this customer? [y/n]: ";

				string deleteConfirmation = "";
				cin >> deleteConfirmation;

				//Clear Buffer
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');


				for (int i = 0; i < deleteConfirmation.length(); i++)
					deleteConfirmation[i] = tolower(deleteConfirmation[i]);


				if (deleteConfirmation == "y" or deleteConfirmation == "yes")
				{
					if (customer.deleteCustomer() and customer.deleteUser())
						cout << "\nCustomer account has been deleted." << endl;
					else
						cout << "Something went wrong. Deleting Process Failed." << endl;

				}
				else
				{
					cout << "Process cancelled, account not deleted." << endl;
				}
			}
		}
		else if (option == "10")
		{
			string search = "";
			cout << "\nEnter Search Keyword: ";
			getline(cin, search);

			Customer customer;

			customer.searchCustomer(search);
		}
		else if (option == "11")
		{
			Admin admin;
            admin.setPassword();
			if (admin.verifyPassword())
				{
					do
					{
						admin.setNewPassword();
					} while (!admin.confirmPass());

					if (admin.updateUser())
						cout << "\nPassword changed successfully!" << endl;
					else
						cout << "Something went wrong." << endl;

				}
				else
					cout << "\nPassword did not match." << endl;
		}
		else if (option == "0")
		{
			cout << "\nYou have logged out of the system." << endl;
			break;
		}
		else
		{
			cout << "\nPlease enter a valid input." << endl;
		}

		cout << "\n\t\tPress any key to continue\n" << endl;
		_getch();

	}
}

void managerMenu(string managerId)
{
	string option;

	while (true)
	{

		cout << "\t\tYou have logged in as MANAGER." << endl;
	    cout << "\n\nMANAGER MENU" << endl << endl << endl;
		
		cout << ".------------------------.-------------------------." << endl;
		cout << ".        CATEGORIES      .         PRODUCTS        ." << endl;
		cout << ".------------------------.-------------------------." << endl;
		cout << ". 1. Add Category        . 6. Add Product          ." << endl;
		cout << ". 2. View Categories     . 7. View Products        ." << endl;
		cout << ". 3. Edit Categories     . 8. Edit Products        ." << endl;
		cout << ". 4. Delete Categories   . 9. Delete Products      ." << endl;
		cout << ". 5. Search Categories   . 10. Search Products     ." << endl;
		cout << ".------------------------.-------------------------." << endl;
		cout << ".         ORDERS         .        CUSTOMERS        ." << endl;
		cout << ".------------------------.-------------------------." << endl;
		cout << ". 11. Add Order          . 17. View Customers      ." << endl;
		cout << ". 12. View Orders        . 18. Search Customer     ." << endl;
		cout << ". 13. Confirm Order      .                         ." << endl;
		cout << ". 14. Edit Orders        .                         ." << endl;
		cout << ". 15. Delete Orders      .                         ." << endl;
		cout << ". 16. Search Orders      .                         ." << endl;
		cout << ".------------------------.-------------------------." << endl; 
		cout << ". 19. Edit Personal Details                       ." << endl;
		cout << ". 0.  Logout                                       ." << endl;
		cout << ".------------------------.-------------------------." << endl;

		cout << "\nWhat do you want to do? : ";
		cin >> option;

		////Clear Buffer
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');


		if (option == "1") // Add Category
		{
			Category category;

			// If the name already exists, it will return to manager menu
			if (category.setName())
			{
				if (category.addCategory())
					cout << "\nNew Category added successfully." << endl;
				else
					cout << "Something went wrong" << endl;
			}

		}
		else if (option == "2") // View Categories
		{
			Category category;

			if (category.countCategory() == 0)
			{
				cout << "\nThere are no categories." << endl;
			}
			else
			{
				category.showAllCategories();
			}
		}
		else if (option == "3") // Edit Categories
		{
			Category category;

			if (category.countCategory() == 0)
			{
				cout << "\nThere are no categories." << endl;
			}
			else
			{
				category.showAllCategories();
				category.chooseCategory();

				// Edit Details in the program
				category.editCategory();

				// Update Details in the file
				category.updateCategory();
			}
		}
		else if (option == "4") // Delete Category
		{
			Category category;
			if (category.countCategory() == 0)
			{
				cout << "\nThere are no categories." << endl;
			}
			else
			{
				category.showAllCategories();
				category.chooseCategory();

				cout << ".~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~." << endl;
				cout << "|          CATEGORY DETAILS           |" << endl;
				cout << ".~~~~~~~~~~~~~~~~~~.~~~~~~~~~~~~~~~~~~." << endl;
				cout << "| 1. Category ID   | " << setw(16) << left << category.categoryId << " |" << endl;
				cout << "| 2. Category Name | " << setw(16) << left << category.name << " |" << endl;
				cout << ".~~~~~~~~~~~~~~~~~~.~~~~~~~~~~~~~~~~~." << endl;

				cout << "Are you sure you want to delete this category? [Y/N]: ";

				string deleteConfirmation = "";
				cin >> deleteConfirmation;

				//Clear Buffer
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');

				for (int i = 0; i < deleteConfirmation.length(); i++)
					deleteConfirmation[i] = tolower(deleteConfirmation[i]);


				if (deleteConfirmation == "y" or deleteConfirmation == "yes")
				{
					// Delete the chosen category
					// Move all the products under that category to Miscellaneous
					category.deleteCategory();

				}
				else
				{
					cout << "Process cancelled." << endl;
				}
			}

		}
		else if (option == "5")
		{
			string search = "";
			cout << "Enter Search Keyword: ";
			getline(cin, search);

			Category category;

			category.searchCategory(search);
		}
		else if (option == "6")	// Add Product
		{
			Product product;

			// Choose from available categories
			product.setCategory();

			product.setName();
			product.setItemPrice();
			product.setPackagingPrice();
			product.setQty();
			product.setDetails();

			if (product.addProduct())
				cout << "\nNew Product has been added." << endl;
			else
				cout << "Something went wrong" << endl;
		}
		else if (option == "7")	// View Products
		{
			Product product;

			if (product.countProduct() == 0)
			{
				cout << "\nThere are no products." << endl;
			}
			else
			{

				string option2 = "";
				while (option2 != "1" and option2 != "2")
				{
					cout << "\n1. View ALL products" << endl;
					cout << "\n2. View products by category" << endl;

					cout << "\nYou would like to see: ";
					cin >> option2;

					////Clear Buffer
					cin.clear();
					cin.ignore(numeric_limits<streamsize>::max(), '\n');

					if (option2 == "1")
					{
						product.showAllProducts();
					}
					else if (option2 == "2")
					{
						product.setCategory();
						product.showProductsByCategory();
					}
					else
					{
						cout << "\nInvalid input." << endl;
					}
				}
			}


		}
		else if (option == "8")	// Edit Product
		{
			Product product;

			if (product.countProduct() == 0)
			{
				cout << "\nThere are no products in inventory." << endl;
			}
			else
			{
				product.showAllProducts();
				product.chooseProduct();

				// Edit product details in the program
				product.editProduct();

				// Update details in the file
				if (product.updateProduct())
					cout << "\nProduct details have been updated successfully." << endl;
				else
					cout << "Something went wrong. Update Failed." << endl;
			}
		}
		else if (option == "9")	// Delete Product
		{
			Product product;
			if (product.countProduct() == 0)
			{
				cout << "\nThere are no products." << endl;
			}
			else
			{
				product.showAllProducts();
				product.chooseProduct();

				Category category(product.categoryId);

				cout << ".~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~." << endl;
				cout << "|               PRODUCT DETAILS                                        |" << endl;
				cout << ".~~~~~~~~~~~~~~~~~~~~~.~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~." << endl;
				cout << "| 1. Product ID       | " << setw(46) << left << product.categoryId << " |" << endl;
				cout << "| 2. Product Name     | " << setw(46) << left << product.name << " |" << endl;
				cout << "| 3. Category ID      | " << setw(46) << left << product.categoryId << " |" << endl;
				cout << "| 4. Category Name    | " << setw(46) << left << category.name << " |" << endl;
				cout << "| 5. Item Price       | RM " << setw(43) << left << product.itemPrice << " |" << endl;
				cout << "| 6. Packaging Price  | RM " << setw(43) << left << product.packagingPrice << " |" << endl;
				cout << "| 7. Quantity         | " << setw(46) << left << product.qty << " |" << endl;
				cout << "| 8. Details          | " << setw(46) << left << product.details << " |" << endl;
				cout << ".~~~~~~~~~~~~~~~~~~~~~.~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~." << endl;

				cout << "Are you sure you want to delete this product? [Y/N]: ";

				string deleteConfirmation = "";
				cin >> deleteConfirmation;

				//Clear Buffer
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');


				for (int i = 0; i < deleteConfirmation.length(); i++)
					deleteConfirmation[i] = tolower(deleteConfirmation[i]);


				if (deleteConfirmation == "y" or deleteConfirmation == "yes")
				{
					// Delete the product form products file
					// Remove the product from cart
					// Change the ID of the product of 0000 in order history
					if (product.deleteProduct())
						cout << "\nProduct has been deleted." << endl;
					else
						cout << "Something went wrong. Deleting Process Failed." << endl;
				}
				else
				{

					cout << "\nProcess cancelled." << endl;

				}
			}


		}
		else if (option == "10")
		{
			string search = "";
			cout << "\nEnter Search Keyword: ";
			getline(cin, search);

			Product product;

			product.searchProduct(search);
		}
		
		else if (option == "11")
		{
			Customer customer;
			if (customer.countCustomer() == 0)
			{
				cout << "\nThere are no customers." << endl;
			}
			else
			{
				customer.showAllCustomers();
				customer.chooseCustomer();

				Product product;
				if (product.countProduct() == 0)
				{
					cout << "\nThere are no products." << endl;
				}
				else
				{
					product.showAllProducts();
					product.chooseProduct();

					Order order(product.productId, customer.customerId);

					if (product.qty == 0)
					{
						cout << "\nThe product is out of stock." << endl;
					}
					else
					{
						order.setQty();
						if (order.addOrder())
							cout << "\nProduct has been added to cart." << endl;
						else
							cout << "\nProduct was not Added to Cart." << endl;
					}

				}

			}


		}
		else if (option == "12")
		{
			Customer customer;
			if (customer.countCustomer() == 0)
			{
				cout << "\nThere is no customer." << endl;
			}
			else
			{
				string option2 = "";
				while (option2 != "1" and option2 != "2" and option2 != "3")
				{
					cout << "1. View All Orders" << endl;
					cout << "2. View Customer's Order History" << endl;
					cout << "3. View Customer's Cart" << endl;

					cout << "\nYou would like to view: ";
					cin >> option2;

					////Clear Buffer
					cin.clear();
					cin.ignore(numeric_limits<streamsize>::max(), '\n');

					if (option2 == "1")
					{
						Order order;
						order.showAllOrders();
					}
					else if (option2 == "2")
					{
						customer.showAllCustomers();
						customer.chooseCustomer();

						Order order(customer.customerId);


						if (order.countItems("Card") == 0 and order.countItems("COD") == 0)
						{
							cout << "\nCustomer has no previous orders." << endl;
						}
						else
						{
							order.showOrdersByCustomer();
						}
					}
					else if (option2 == "3")
					{
						customer.showAllCustomers();
						customer.chooseCustomer();

						Order order(customer.customerId);


						if (order.countItems("Cart") == 0)
						{
							cout << "\nThe cart is empty." << endl;
						}
						else
						{
							order.showCart();
						}
					}
					else
					{
						cout << "\nPlease enter a valid input." << endl;
					}
				}

			}
		}
		else if (option == "13")
		{
			Customer customer;
			customer.showAllCustomers();
			customer.chooseCustomer();

			Order order(customer.customerId);

			order.validateCart();
			if (order.countItems("Cart") == 0)
			{
				cout << "\nThe cart is empty." << endl;
			}
			else
			{
				order.Bill();
				cout << "\nAre you sure you want to confirm the order with COD? [Y/N]: ";

				string confirmation = "";
				cin >> confirmation;

				//Clear Buffer
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');

				for (int i = 0; i < confirmation.length(); i++)
					confirmation[i] = tolower(confirmation[i]);


				if (confirmation == "y" or confirmation == "yes")
				{
					string paymentMethod = "COD";
					order.Pay(paymentMethod);

				}
				else
				{
					cout << "\nOrder was not confirmed." << endl;
				}

			}

		}
		else if (option == "14")
		{
			cout << "\nYou can only edit existing products in cart." << endl;
			Customer customer;
			customer.showAllCustomers();
			customer.chooseCustomer();

			Order order(customer.customerId);

			order.validateCart();
			if (order.countItems("Cart") == 0)
			{
				cout << "\nThe cart is empty." << endl;
			}
			else
			{
				order.showCart();

				order.chooseCartItem();

				order.editCartQty();

				order.updateCart();
			}
		}
		else if (option == "15")
		{
			cout << "\nYou can only delete existing products in the cart." << endl;
			Customer customer;
			
			customer.showAllCustomers();
			customer.chooseCustomer();

			Order order(customer.customerId);
			order.validateCart();
			if (order.countItems("Cart") == 0)
			{
				cout << "\nCart is empty." << endl;
			}
			else
			{
				order.showCart();

				order.chooseCartItem();

				Product product(order.productId);
				
				cout << ".~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~." << endl;
				cout << "|                   ORDER DETAILS                 |" << endl;
				cout << ".~~~~~~~~~~~~~~~~~~~~~~~~.~~~~~~~~~~~~~~~~~~~~~~~~." << endl;
				cout << "| Order ID               | " << setw(22) << left << order.orderId << " |" << endl;
				cout << "| Product ID             | " << setw(22) << left << order.productId << " |" << endl;
				cout << "| Product Name           | " << setw(22) << left << product.name << " |" << endl;
				cout << "| Current Quantity       | " << setw(22) << left << order.qty << " |" << endl;
				cout << "| Available in Stock     | " << setw(22) << left << product.qty << " |" << endl;
				cout << "| Item Price             | RM " << setw(19) << left << fixed << setprecision(2) 	<< product.itemPrice << " |" << endl;
				cout << "| Packaging Price        | RM " << setw(19) << left << fixed << setprecision(2) 	<< product.packagingPrice << " |" << endl;
				cout << "| Total Price per Unit   | RM " << setw(19) << left << fixed << setprecision(2) 	<< product.itemPrice + product.packagingPrice << " |" << endl;
				cout << "| Current Total Price    | RM " << setw(19) << left << fixed << setprecision(2) 	<< order.qty * (product.itemPrice + product.packagingPrice) << " |" << endl;
				cout << ".~~~~~~~~~~~~~~~~~~~~~~~~.~~~~~~~~~~~~~~~~~~~~~~~~." << endl;

				cout << "\nAre you sure you want to delete this item from user's cart? [Y/N]: ";

				string deleteConfirmation = "";
				cin >> deleteConfirmation;

				//Clear Buffer
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');


				for (int i = 0; i < deleteConfirmation.length(); i++)
					deleteConfirmation[i] = tolower(deleteConfirmation[i]);


				if (deleteConfirmation == "y" or deleteConfirmation == "yes")
					order.deleteCartItem();
				else
					cout << "\nDeleting Process Cancelled." << endl;
			}
		}
		else if (option == "16")
		{
			string search = "";
			cout << "\nEnter Search Keyword: ";
			getline(cin, search);

			Order order;
			order.searchOrder(search);
		}
		else if (option == "17") // View Customers
		{
			Customer customer;
			if (customer.countCustomer() == 0)
			{
				cout << "\nThere is no registered customer." << endl;
			}
			else
			{
				customer.showAllCustomers();
			}
		}
		else if (option == "18")
		{
			string search = "";
			cout << "Enter Search Keyword: ";
			getline(cin, search);

			Customer customer;

			customer.searchCustomer(search);
		}
		else if (option == "19")
		{
			Manager manager(managerId);

			// Edit Manager details in the program
			manager.editPersonalDetails();

			// Update the manager details in the files
			if (manager.updateManager() and manager.updateUser())
				cout << "\nYour details have been updated." << endl;
			else
				cout << "Something went wrong. Update Failed." << endl;
		}
		else if (option == "0")
		{
			cout << "\nYou have logged out of the system." << endl;
			break;
		}
		else
		{
			cout << "\nPlease enter a valid input." << endl;
		}

		cout << "\n\t\tPress any key to continue.\n" << endl;
		_getch();
	}
}


void customerMenu(string customerId)
{
	string choice;
	while (true)
	{
    
	    cout << "\t\tYou have logged in as CUSTOMER." << endl;
	    cout << "\n\nCUSTOMER MENU" << endl << endl << endl;
		
		cout << ".------------------------------." << endl;
		cout << ".             MENU             ." << endl;
		cout << ".------------------------------." << endl;
		cout << ". 1. View All Products         ." << endl;
		cout << ". 2. Search for Products       ." << endl;
		cout << ". 3. Add Product to Cart       ." << endl;
		cout << ". 4. View Cart                 ." << endl;
		cout << ". 5. Edit Cart                 ." << endl;
		cout << ". 6. Delete Product in Cart    ." << endl;
		cout << ". 7. Checkout                  ." << endl;
		cout << ". 8. Order History             ."  << endl;
		cout << ".------------------------------." << endl; 
		cout << ". 9. Edit Personal Details     ." << endl;
		cout << ". 0. Logout                   ." << endl;
		cout << ".------------------------------." << endl;

		cout << "\nWhat do you want to do? : ";
		cin >> choice;

		////Clear Buffer
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');

		if (choice == "1")
		{
			Product product;

			if (product.countProduct() == 0)
			{
				cout << "\nThere are no products in the store!" << endl;
			}
			else
			{
				string choice2 = "";
				while (choice2 != "1" and choice2 != "2")
				{
					cout << "\n1. View ALL products" << endl << endl;
					cout << "\n2. View Products by Category" << endl << endl;

					cout << "\nYou want to view: ";
					cin >> choice2;

					////Clear Buffer
					cin.clear();
					cin.ignore(numeric_limits<streamsize>::max(), '\n');

					if (choice2 == "1")
					{
						product.showAllProducts();
					}
					else if (choice2 == "2")
					{
						product.setCategory();
						product.showProductsByCategory();
					}
					else
					{
						cout << "Invalid input. Try again." << endl;
					}
				}
			}
		}
		else if (choice == "2")
		{
			string search = "";
			cout << "Enter search keyword: ";
			getline(cin, search);

			Product product;

			product.searchProduct(search);
		}
		else if (choice == "3")
		{
			Product product;

			if (product.countProduct() == 0)
			{
				cout << "\nThere is no product in store!" << endl;
			}
			else
			{
				product.showAllProducts();
				product.chooseProduct();

				Order order(product.productId, customerId);

				if (product.qty == 0)
				{
					cout << "\nProduct is out of stock." << endl;
				}
				else
				{
					order.setQty();
					if (order.addOrder())
						cout << "\nProduct added to cart successfully." << endl;
					else
						cout << "\nProduct could not be added to cart." << endl;
				}
			}


		}
		else if (choice == "4") // View Cart
		{
			Order order(customerId);

			order.validateCart();
			if (order.countItems("Cart") == 0)
			{
				cout << "\nThe cart is empty." << endl;
			}
			else
			{
				order.showCart();
			}

		}
		else if (choice == "5") // Edit Cart
		{
			Order order(customerId);

			order.validateCart();
			if (order.countItems("Cart") == 0)
			{
				cout << "\nThe cart is empty." << endl;
			}
			else
			{
				order.showCart();

				order.chooseCartItem();

				order.editCartQty();

				order.updateCart();
			}

		}
		else if (choice == "6")
		{
			Order order(customerId);
			order.validateCart();
			if (order.countItems("Cart") == 0)
			{
				cout << "\nThe cart is empty." << endl;
			}
			else
			{
				order.showCart();

				order.chooseCartItem();

				Product product(order.productId);
				//Show the data

				cout << ".~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~." << endl;
				cout << "|                   ORDER DETAILS                 |" << endl;
				cout << ".~~~~~~~~~~~~~~~~~~~~~~~~.~~~~~~~~~~~~~~~~~~~~~~~~." << endl;
				cout << "| Order ID               | " << setw(22) << left << order.orderId << " |" << endl;
				cout << "| Product ID             | " << setw(22) << left << order.productId << " |" << endl;
				cout << "| Product Name           | " << setw(22) << left << product.name << " |" << endl;
				cout << "| Current Quantity       | " << setw(22) << left << order.qty << " |" << endl;
				cout << "| Available in Stock     | " << setw(22) << left << product.qty << " |" << endl;
				cout << "| Item Price             | RM " << setw(19) << left << fixed << setprecision(2) 
					<< product.itemPrice << " |" << endl;
				cout << "| Packaging Price        | RM " << setw(19) << left << fixed << setprecision(2) 
					<< product.packagingPrice << " |" << endl;
				cout << "| Total Price per Unit   | RM " << setw(19) << left << fixed << setprecision(2) 
					<< product.itemPrice + product.packagingPrice << " |" << endl;
				cout << "| Current Total Price    | RM " << setw(19) << left << fixed << setprecision(2) 
					<< order.qty * (product.itemPrice + product.packagingPrice) << " |" << endl;
				cout << ".~~~~~~~~~~~~~~~~~~~~~~~~.~~~~~~~~~~~~~~~~~~~~~~~~." << endl;

				cout << "\nAre you sure you want to delete this item from your cart? [Y/N]: ";
				
				

				string deleteConfirmation = "";
				cin >> deleteConfirmation;

				//Clear Buffer
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');


				for (int i = 0; i < deleteConfirmation.length(); i++)
					deleteConfirmation[i] = tolower(deleteConfirmation[i]);


				if (deleteConfirmation == "y" or deleteConfirmation == "yes")
					order.deleteCartItem();
				else
					cout << "\nDeleting Process Cancelled" << endl;
			}
		}
		else if (choice == "7")
		{
			Order order(customerId);
			order.validateCart();
			if (order.countItems("Cart") == 0)
			{
				cout << "\nCart is empty" << endl;
			}
			else
			{
				order.Bill();

				string paymentChoice, paymentMethod;

				while (true)
				{
					cout << "\nAvailable Payment Methods:" << endl;
					cout << "\n1. Pay by Debit/Credit card" << endl;
					cout << "\n2. Cash On Delivery (COD)" << endl;

					cout << "\nChoose a Payment Method: ";
					cin >> paymentChoice;

					////Clear Buffer
					cin.clear();
					cin.ignore(numeric_limits<streamsize>::max(), '\n');

					if (paymentChoice == "1")
					{
						paymentMethod = "Card";
						break;
					}
					else if (paymentChoice == "2")
					{
						paymentMethod = "COD";
						break;
					}
					else
					{
						cout << "Invalid input. Try again." << endl;
					}
				}


				order.Pay(paymentMethod);
			}

		}
		else if (choice == "8")
		{
			Order order(customerId);

			if (order.countItems("Card") == 0 and order.countItems("COD") == 0)
			{
				cout << "\nOrder history is empty" << endl;
			}
			else
			{
				order.showOrderHistory();
			}

		}
		else if (choice == "9")
		{
			Customer customer(customerId);

			// Edit Manager details in the program
			customer.editPersonalDetails();

			// Update the manager details in the files
			if (customer.updateCustomer() and customer.updateUser())
				cout << "\nYour personal details have been updated." << endl;
			else
				cout << "\nSomething went wrong. Update Failed." << endl;
		}
		else if (choice == "0")
		{
			cout << "\nYou have been logged out of the system." << endl;
			break;
		}
		else
		{
			cout << "\nPlease enter a valid input." << endl;
		}

		cout << "\n\t\tPress any key to continue.\n" << endl;
		_getch();
	}

}


int main()
{
	headers();

	string option = "";
	while (option != "0")
	{
		cout << "\tONLINE SHOPPING MANAGEMENT SYSTEM" << endl;
		cout << ".-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-." << endl;
		cout << endl;
	
        cout << ".------------------------------." << endl;
		cout << ".             MENU             ." << endl;
		cout << ".------------------------------." << endl;
		cout << ". 1. Login (registered users)  ." << endl;
		cout << ". 2. Register as Customer      ." << endl;
		cout << ". 3. Forgot Password?          ." << endl;
		cout << ". 0. Exit the store            ." << endl;
		cout << ".------------------------------." << endl;
	
        
		cout << "\nWhat do you want to do?: ";
		cin >> option;

		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');


		if (option == "1")//Login
		{
			User user;

			user.setEmail();
			user.setPassword();

			if (user.verifyPassword())
			{
				if (user.userType == "admin")
					adminMenu();
				else if (user.userType == "manager")
				{
					Manager manager(user.email);
					managerMenu(manager.managerId);
				}

				else if (user.userType == "customer")
				{
					Customer customer(user.email);
					customerMenu(customer.customerId);
				}

			}
			else
			{
				cout << "\nThis account does not exist.\nPlease check your email and password and try again." << endl;
			}

		}
		else if (option == "2")//Register
		{
			Customer customer;

			customer.setName();
			if (customer.setNewEmail())
			{
				customer.setPhone();
				do
				{
					customer.setNewPassword();
				} while (!customer.confirmPass());

				customer.setAddress();
				if (customer.addUser() && customer.addCustomer())
				{

					customerMenu(customer.customerId);
				}
			}
		}
		
		else if (option == "3")
		{
			cout << "\nUnfortunately, you cannot change the password. Please email our manager or admin at support@helpdesk.com with your email and full name so they can change your password.";
			cout << "Thank you for your patience, please try logging in after you receive a confirmation email." << endl;
		}
		
		else if (option == "0")
		{
			cout << "\nYou are now exiting the online store." << endl;
			break;
		}
		else
		{
			cout << "\nPlease enter a valid input!" << endl;
		}

		cout << "\n\t\tPress any key to continue" << endl;
		_getch();

		system("cls");

	}
}
