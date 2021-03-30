#pragma once


class Object {
public:
	
	Object();
	Object(int value);
	Object(const Object& obj);
	~Object();

	Object& operator=(const Object& obj);

	int getValue() const;
	void setValue(int newValue);

	void whatAmI() const;


protected:
	int id_;
	int value_;

private:
	static int objectCount_;

};
