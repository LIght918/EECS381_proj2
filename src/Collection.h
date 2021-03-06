#ifndef COLLECTION_H
#define COLLECTION_H

/* Collections contain a name and a container of members,
represented as pointers to Records.
Collection objects manage their own Record container. 
The container of Records is not available to clients.
*/

/* *** NOTE: If after a function header is a comment "fill this in" remove the comment and replace
it with the proper code here in the header file.  All other functions should be defined
in the .cpp file. 
Comments starting with "***" are instructions to you - remove them from your finished code.
Remove this comment too. */

#include "String.h"
#include "Ordered_list.h"
#include <iosfwd>

class Record;

class Collection {
    

public:
	// Construct a collection with the specified name and no members
	Collection(const String& name_);
	/*fill this in*/
	
	/* Construct a Collection from an input file stream in save format, using the record list,
	restoring all the Record information.
	Record list is needed to resolve references to record members.
	No check made for whether the Collection already exists or not.
	Throw Error exception if invalid data discovered in file.
	String data input is read directly into the member variable. */
    Collection( std::ifstream& is, const Ordered_list<Record*, Less_than_ptr<Record*>>& library );

	// Accessors
	String get_name() const
    { return name; }
		
	// Add the Record, throw exception if there is already a Record with the same title.
	void add_member(Record* record_ptr);
	// Return true if there are no members; false otherwise
	bool empty() const
    { return lib.empty(); }
	// Return true if the record is present, false if not.
	bool is_member_present(Record* record_ptr) const;
	// Remove the specified Record, throw exception if the record was not found.
	void remove_member(Record* record_ptr);
	// discard all members
	void clear()
    { lib.clear(); }

	// Write a Collections's data to a stream in save format, with endl as specified.
	void save(std::ostream& os) const;

	// This operator defines the order relation between Collections, based just on the name
	bool operator< (const Collection& rhs) const
    { return name < rhs.get_name(); }
	
    friend std::ostream& operator<< (std::ostream& os, const Collection& collection);
    
private:
	/* *** the member information must be kept in a container of Record* - name is your choice */
    Ordered_list<Record*, Less_than_ptr<Record*>> lib;

	/* *** other private members are your choice */
    String name;
};

// Print the Collection data
std::ostream& operator<< (std::ostream& os, const Collection& collection);

#endif
