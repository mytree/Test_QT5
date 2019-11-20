
#pragma once

/*
	
*/

class C0205_Struct : public ITestObject {
public:
	struct man {
		char	*Name;
		int		Age;
		int		Feet;
		int		Weight;
	};

	void setMan(struct man *men, char *name, int age, int feet, int weight) {
		men->Name = (char*)malloc(strlen(name));
		strcpy(men->Name, name);
		men->Age = age;
		men->Feet = feet;
		men->Weight = weight;
	}
	void printName(struct man *men) {
		printf("Name : %s\n", men->Name);
	}
	void printAge(struct man *men) {
		printf("Age : %d\n", men->Age);
	}
	void printFeet(struct man *men) {
		printf("Feet : %d\n", men->Feet);
	}
	void printWeight(struct man *men) {
		printf("Weight : %d\n", men->Weight);
	}

	virtual int OnTest(int nArgNum, char** ppArgs) {
		struct man *Julia;
		Julia = (struct man*)malloc(sizeof(struct man));
		setMan(Julia, (char*)"Julia", 23, 168, 55);
		printName(Julia);
		printAge(Julia);
		printFeet(Julia);
		printWeight(Julia);
		free(Julia);
		return 0;
	}
};
