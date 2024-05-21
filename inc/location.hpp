#ifndef LOCATION_HPP
#define LOCATION_HPP

class Location
{
	private:
		std::string _path;
		std::string _root;
	public:
		Location();
		~Location();

		void setPath(std::string const);
		void setRoot(std::string const);

		std::string getPath() const;
		std::string getRoot() const;
};

std::ostream &operator<<(std::ostream &stream, Location & arg);

#endif//LOCATION_HPP