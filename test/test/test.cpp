// Uncomment the next line to use precompiled headers
#include "pch.h"
// uncomment the next line if you do not use precompiled headers
//#include "gtest/gtest.h"
//
// the global test environment setup and tear down
// you should not need to change anything here
class Environment : public ::testing::Environment
{
public:
    ~Environment() override {}

    // Override this to define how to set up the environment.
    void SetUp() override
    {
        //  initialize random seed
        srand(time(nullptr));
    }

    // Override this to define how to tear down the environment.
    void TearDown() override {}
};

// create our test class to house shared data between tests
// you should not need to change anything here
class CollectionTest : public ::testing::Test
{
protected:
    // create a smart point to hold our collection
    std::unique_ptr<std::vector<int>> collection;

    void SetUp() override
    { // create a new collection to be used in the test
        collection.reset(new std::vector<int>);
    }

    void TearDown() override
    { //  erase all elements in the collection, if any remain
        collection->clear();
        // free the pointer
        collection.reset(nullptr);
    }

    // helper function to add random values from 0 to 99 count times to the collection
    void add_entries(int count)
    {
        assert(count > 0);
        for (auto i = 0; i < count; ++i)
            collection->push_back(rand() % 100);
    }
};

// When should you use the EXPECT_xxx or ASSERT_xxx macros?
// Use ASSERT when failure should terminate processing, such as the reason for the test case.
// Use EXPECT when failure should notify, but processing should continue

// Test that a collection is empty when created.
// Prior to calling this (and all other TEST_F defined methods),
//  CollectionTest::StartUp is called.
// Following this method (and all other TEST_F defined methods),
//  CollectionTest::TearDown is called
TEST_F(CollectionTest, CollectionSmartPointerIsNotNull)
{
    // is the collection created
    ASSERT_TRUE(collection);

    // if empty, the size must be 0
    ASSERT_NE(collection.get(), nullptr);
}

// Test that a collection is empty when created.
TEST_F(CollectionTest, IsEmptyOnCreate)
{
    // is the collection empty?
    ASSERT_TRUE(collection->empty());

    // if empty, the size must be 0
    ASSERT_EQ(collection->size(), 0);
}

/* Comment this test out to prevent the test from running
 * Uncomment this test to see a failure in the test explorer */
TEST_F(CollectionTest, AlwaysFail)
{
    FAIL();
}

// TODO: Create a test to verify adding a single value to an empty collection
TEST_F(CollectionTest, CanAddToEmptyVector)
{
    // is the collection empty?
    // if empty, the size must be 0
    ASSERT_TRUE(collection->empty());   //the collection should be empty
    ASSERT_EQ(collection->size(), 0);   //the collection size should equal to zero

    add_entries(1);

    // is the collection still empty?
    // if not empty, what must the size be?
    ASSERT_FALSE(collection->empty());  //the collection should no longer be empty - negative test
    ASSERT_EQ(collection->size(), 1);  //the collection size should have one more entry - size++
}

// TODO: Create a test to verify adding five values to collection
TEST_F(CollectionTest, CanAddFiveValuesToVector)
{
    add_entries(5);
    ASSERT_EQ(collection->size(), 5); //the collection size should be equal to the 5 entries added
}

// TODO: Create a test to verify that max size is greater than or equal to size for 0, 1, 5, 10 entries
TEST_F(CollectionTest, MaxSizeGreaterThanOrEqualToSize) 
{   
    ASSERT_TRUE(collection->max_size() >= 0); //max size is greater than or equal to 0
    ASSERT_TRUE(collection->max_size() >= 1); //max size is greater than or equal to 1
    ASSERT_TRUE(collection->max_size() >= 5); //max size is greater than or equal to 5
    ASSERT_TRUE(collection->max_size() >= 10); //max size is greater than or equal to 10
    std::cout << "Check Collection Max Size: " << collection->max_size() << std::endl; //peace of mind output
}

// TODO: Create a test to verify that capacity is greater than or equal to size for 0, 1, 5, 10 entries
TEST_F(CollectionTest, CapacityIsGreaterThanOrEqualToSize)
{
    add_entries(10);
    ASSERT_TRUE(collection->capacity() >= 0); //capacity greater than or equal to 0
    ASSERT_TRUE(collection->capacity() >= 1); //capacity greater than or equal to 1
    ASSERT_TRUE(collection->capacity() >= 5); //capacity greater than or equal to 5
    ASSERT_TRUE(collection->capacity() >= 10); //capacity greater than or equal to 10
    std::cout << "Check Capacity Size: " << collection->capacity() << std::endl; //peace of mind output
}

// TODO: Create a test to verify resizing increases the collection
TEST_F(CollectionTest, ResizingIncreasesTheCollection) 
{
    add_entries(10); //add to collection
    int tempSize = collection->size(); //store previous collection size

    collection->resize(15); //resize collection

    ASSERT_TRUE(collection->size() > tempSize); //collection increased from the previous collection size

    std::cout << "Before Increase Resizing: " << tempSize << " / After Increase Resizing: " << collection->size() << std::endl; //peace of mind output
}

// TODO: Create a test to verify resizing decreases the collection
TEST_F(CollectionTest, ResizingDecreasesTheCollection) 
{
    add_entries(10); //add to collection
    int tempSize = collection->size(); //store previous collection size

    collection->resize(5); //resize collection

    ASSERT_TRUE(collection->size() < tempSize); //collection decreased from the previous collection size

    std::cout << "Before Decrease Resizing: " << tempSize << " / After Decrease Resizing: " << collection->size() << std::endl; //peace of mind output
}

// TODO: Create a test to verify resizing decreases the collection to zero
TEST_F(CollectionTest, ResizingDecreasesTheCollectionToZero)
{
    add_entries(10);
    int tempSize = collection->size(); //store previous collection size

    collection->resize(0); //resize collection to zero

    ASSERT_EQ(collection->size(), 0); //resizing decreased the collection to zero - will be equal to 0 / could also use ASSERT_TRUE(collection->empty());

    std::cout << "Before Decrease Resizing To Zero: " << tempSize << " / After Decrease Resizing To Zero: " << collection->size() << std::endl; //peace of mind output
}

// TODO: Create a test to verify clear erases the collection
TEST_F(CollectionTest, ClearErasesCollection) 
{
    add_entries(10); //add to collection
    collection->clear(); //clear collection
    ASSERT_TRUE(collection->empty()); //clear erased the collection and is now empty / could also use ASSERT_EQ(collection->size(), 0);
}

// TODO: Create a test to verify erase(begin,end) erases the collection
TEST_F(CollectionTest, EraseErasesTheCollection) 
{
    add_entries(10); //add to collection
    collection->erase(collection->begin(), collection->end()); //erase begin, end collection
    ASSERT_TRUE(collection->empty()); //erase erased the collection / could also use ASSERT_EQ(collection->size(), 0);
}

// TODO: Create a test to verify reserve increases the capacity but not the size of the collection
TEST_F(CollectionTest, ReserveIncreasesTheCapacityButNotSize) 
{
    add_entries(10); //add to collection
    int tempCapacity = collection->capacity(); //store previous capacity data 
    int tempSize = collection->size(); //store previous size data

    collection->reserve(15); //reserve 15

    ASSERT_TRUE(collection->capacity() > tempCapacity); //collection capacity is greater than previous capacity data
    ASSERT_EQ(collection->size(), tempSize); //collection size will NOT be greater than tempSize, they will be equal

    //peace of mind outputs
    std::cout << "Before Reserve Capacity: " << tempCapacity << " / After Reserve Capacity: " << collection->capacity() << std::endl;
    std::cout << "Before Reserve Size: " << tempSize << " / After Reserve Size: " << collection->size() << std::endl;
}

// TODO: Create a test to verify the std::out_of_range exception is thrown when calling at() with an index out of bounds
// NOTE: This is a negative test
TEST_F(CollectionTest, OutOfRangeThrownWhenIndexOutOfBounds)
{
    std::vector<int> tempVector(10, 0); //initialize vector with value
    EXPECT_THROW(tempVector.at(15), std::out_of_range); //expect out of range exception being thrown when out of bounds
}

// TODO: Create 2 unit tests of your own to test something on the collection - do 1 positive & 1 negative
TEST_F(CollectionTest, VerifySizeWorks)
{
    add_entries(10); //add 10
    ASSERT_EQ(collection->size(), 10); //collection size should be 10

    add_entries(5); //add 5 ontop of 10
    ASSERT_EQ(collection->size(), 15); //collection size should be 15

    collection->resize(5); //resize to 5
    ASSERT_EQ(collection->size(), 5); //collection size should be 5

    collection->clear(); //clear collection
    ASSERT_EQ(collection->size(), 0); //collection size should be 0

    add_entries(1); //add 1
    ASSERT_FALSE(collection->size() == 0); //negative - collection size should not be 0
}

TEST_F(CollectionTest, subtractEntries)
{
    //push_back was tested within add_entries (ln 49)
    add_entries(10); //add 10

    collection->pop_back(); //subtract 1
    ASSERT_EQ(collection->size(), 9); //positive - collection size should be 9

    collection->pop_back(); //subtract 1
    ASSERT_FALSE(collection->size() == 9); //negative - collection size should no longer be 9
}

//tried to check for overflow and underflow but was unable to figure out how to make it a unit test