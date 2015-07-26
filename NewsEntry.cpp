#include "NewsEntry.h"

using namespace std;
NewsEntry::NewsEntry(){
	 mTitle = " ";
	 mDescription = " ";
	 mPubDate = " ";
	 mLink = " ";
}

void NewsEntry::setTitle(const char* title){
	mTitle = title ;
}
void NewsEntry::setDescription(const char* descript){
	mDescription = descript;
}
void NewsEntry::setPubDate(const char* pubDate){
	mPubDate = pubDate;
}
void NewsEntry::setLink(const char* link){
	mLink = link;
}

std::string NewsEntry::getTitle(){
	return mTitle;
}
		
std::string NewsEntry::getDescription(){
	return mDescription;
}		
std::string NewsEntry::getPubdate(){
	return mPubDate;
}
std::string NewsEntry::getLink(){
	return mLink;
}
