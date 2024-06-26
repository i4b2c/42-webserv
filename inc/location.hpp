#ifndef LOCATION_HPP
#define LOCATION_HPP

class Location
{
	private:
		std::string _path;
		std::string _root;
		bool		_auto_index;
	public:
		Location();
		~Location();

		void setPath(std::string const);
		void setRoot(std::string const);
		void setAutoIndex(bool const auto_index_temp);

		std::string getPath() const;
		std::string getRoot() const;
		std::string getAutoIndex() const;
};

std::ostream &operator<<(std::ostream &stream, Location & arg);

#endif//LOCATION_HPP