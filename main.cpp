#include <iostream>
#include <iomanip>
#include <vector>
#include <limits>		// for numeric_limits
using namespace std;

class MenuItem
{
public:
  string name;
  double price;

    MenuItem (const string & itemName, double itemPrice):name (itemName),
    price (itemPrice)
  {
  }
};

class OrderItem
{
public:
  string name;
  int quantity;

    OrderItem (const string & itemName, int itemQuantity):name (itemName),
    quantity (itemQuantity)
  {
  }
};

class FoodMenu
{
private:
  vector < MenuItem > menu;

public:
  void addItem (const string & itemName, double itemPrice)
  {
    menu.push_back (MenuItem (itemName, itemPrice));
  }

  void displayMenu () const
  {
    cout << "-------------------MENU-------------------\n";
    cout << setw (20) << "Item" << setw (10) << "Price\n";
    cout << "-------------------------------------------\n";
    for (const auto & item:menu)
      {
	cout << setw (20) << item.name << setw (10) << item.price << "\n";
      }
    cout << "-------------------------------------------\n";
  }

  double getPrice (const string & itemName) const
  {
    for (const auto & item:menu)
      {
	if (item.name == itemName)
	  {
	    return item.price;
	  }
      }
    return -1.0;		// Indicate item not found
  }
};

class Order
{
private:
  vector < OrderItem > order;

public:
  void addItem (const string & itemName, int quantity)
  {
    order.push_back (OrderItem (itemName, quantity));
  }

  void displayOrder () const
  {
    cout << "\n-------------------ORDER-------------------\n";
    cout << setw (20) << "Item" << setw (10) << "Quantity\n";
    cout << "-------------------------------------------\n";
    for (const auto & item:order)
      {
	cout << setw (20) << item.name << setw (10) << item.quantity << "\n";
      }
    cout << "-------------------------------------------\n";
  }

  double calculateTotal (const FoodMenu & foodMenu) const
  {
    double total = 0.0;
    for (const auto & item:order)
      {
	double price = foodMenu.getPrice (item.name);
	  total += (price * item.quantity);
      }
    return total;
  }
};

void
displayOptions ()
{
  cout << "\n-----------------OPTIONS-----------------\n";
  cout << "1. Display Menu\n";
  cout << "2. Add Item to Order\n";
  cout << "3. Display Order\n";
  cout << "4. Generate Bill\n";
  cout << "5. Exit\n";
  cout << "------------------------------------------\n";
}

int
main ()
{
  FoodMenu foodMenu;
  foodMenu.addItem ("Burger", 139);
  foodMenu.addItem ("Pizza", 250);
  foodMenu.addItem ("Pasta", 120);
  // Add more items as needed

  Order order;

  int choice;
  do
    {
      displayOptions ();
      cout << "Enter your choice: ";
      cin >> choice;

      switch (choice)
	{
	case 1:
	  foodMenu.displayMenu ();
	  break;
	case 2:
	  {
	    string itemName;
	    int quantity;
	    cout << "Enter item name: ";
	    cin >> itemName;
	    cout << "Enter quantity: ";
	    cin >> quantity;
	    order.addItem (itemName, quantity);
	    break;
	  }
	case 3:
	  order.displayOrder ();
	  break;
	case 4:
	  {
	    double total = order.calculateTotal (foodMenu);
	    cout << "Total Bill: Rs. " << fixed << setprecision (2) << total
	      << "\n";
	    break;
	  }
	case 5:
	  cout << "Exiting the program.\n";
	  break;
	default:
	  cout << "Invalid choice. Please enter a valid option.\n";
	  cin.clear ();		// clear input buffer to restore cin to a usable state
	  cin.ignore (numeric_limits < streamsize >::max (), '\n');	// ignore last input
	  break;
	}
    }
  while (choice != 5);

  return 0;
}
