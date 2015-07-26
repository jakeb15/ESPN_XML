#include <string>
#include <iostream>

class NewsEntry{


	public: 
		NewsEntry();
		void setTitle(const char* title);
		void setDescription(const char* descript);
		void setPubDate(const char* pubDate);
		void setLink(const char* link);
		std::string getTitle();
		std::string getDescription();
		std::string getPubdate();
		std::string getLink();
		

	private:
		std::string mTitle;
		std::string mDescription;
		std::string mPubDate;
		std::string mLink;

};