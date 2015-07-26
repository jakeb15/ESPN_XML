// ESPN_XML.cpp : Defines the entry point for the console application.

#define CURL_STATICLIB
#include <stdio.h>
#include <curl/curl.h>
#include <curl/types.h>
#include <curl/easy.h>
#include <string>
#include "tinyxml2.h"
#include <iostream>
#include "NewsEntry.h"
#include <fstream>
#include <MMSystem.h>


using namespace tinyxml2;

//call back function
size_t write_data(void *ptr, size_t size, size_t nmemb, FILE *stream) {
    size_t written;
    written = fwrite(ptr, size, nmemb, stream);
    return written;
}

int main()
{
	
	bool soundFlag = false;
	std::string headlines[3000];
	int strCount = 0;
	bool storyExists = false;
	int pageSwitch = 0;
while (true){
	std::ofstream a_file ( "ESPN_NEWS.txt", std::ios::app );
	CURL *curl;
    FILE *fp;
    CURLcode res;
	if (pageSwitch==0){
		char *url = "http://sports.espn.go.com/espn/rss/news";
		char outfilename[FILENAME_MAX] = "input3.xml";
	    curl = curl_easy_init();
	    if (curl) {
			fp = fopen(outfilename,"wb");
			curl_easy_setopt(curl, CURLOPT_URL, url);
			curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
			curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp);
			res = curl_easy_perform(curl);
			curl_easy_cleanup(curl);
			fclose(fp);
	   }
	}
	else if(pageSwitch==1){
		char *url = "http://sports.espn.go.com/espn/rss/nfl/news";
		char outfilename[FILENAME_MAX] = "input3.xml";
		curl = curl_easy_init();
		if (curl) {
		     fp = fopen(outfilename,"wb");
			 curl_easy_setopt(curl, CURLOPT_URL, url);
			 curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
			 curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp);
			 res = curl_easy_perform(curl);
			 curl_easy_cleanup(curl);
			 fclose(fp);
		}
	}
	else if(pageSwitch==2){
		char *url = "http://sports.espn.go.com/espn/rss/nba/news";
		char outfilename[FILENAME_MAX] = "input3.xml";
	    curl = curl_easy_init();
	    if (curl) {
		 fp = fopen(outfilename,"wb");
		 curl_easy_setopt(curl, CURLOPT_URL, url);
		 curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
		 curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp);
		 res = curl_easy_perform(curl);
		 curl_easy_cleanup(curl);
		 fclose(fp);
		}
	}
	else{
	  char *url = "http://sports.espn.go.com/espn/rss/espnu/news";
	  char outfilename[FILENAME_MAX] = "input3.xml";
	  curl = curl_easy_init();
	  if (curl) {
        fp = fopen(outfilename,"wb");
        curl_easy_setopt(curl, CURLOPT_URL, url);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp);
        res = curl_easy_perform(curl);
        curl_easy_cleanup(curl);
        fclose(fp);
	  }
	}

	////////////////////////////////////////////////////////////////
	bool loopFlag = true;
	bool bigLoop = true;
	
    tinyxml2::XMLDocument doc;
    doc.LoadFile( "input3.xml" );
	XMLNode *rootnode = doc.FirstChild();
	//////////////////////////////
	rootnode = rootnode->NextSibling();
	rootnode = rootnode->FirstChild();////////////hard code to get past the xml header into <ITEM> </ITEM portion
	rootnode = rootnode->FirstChild();
	rootnode = rootnode->NextSibling();
	///////////////////////////////////
	
	while(loopFlag==true){
		if(std::strcmp(rootnode->Value(),"item") != 0){   
			rootnode = rootnode->NextSibling();
		}
		else 
			loopFlag=false;
	}


	while(bigLoop==true){
		XMLHandle safe = rootnode;
		if(safe.ToNode()==NULL)
			bigLoop=false;
		else{
			NewsEntry *story = new NewsEntry(); 
			rootnode = rootnode->FirstChild();
			rootnode = rootnode->NextSibling();
			rootnode = rootnode->FirstChild();
			story->setTitle(rootnode->Value());
			for(int x=0; x<strCount; x++){
				if(story->getTitle().compare(headlines[x])==0){
					storyExists = true;
				}

			}	

			if(storyExists==false){
				if(soundFlag==true){
					PlaySound(TEXT("sportscenter.wav"), NULL, SND_FILENAME | SND_ASYNC);
				}
				std::cout<< story->getTitle() <<std::endl;
				a_file << story->getTitle();
				a_file << "\n";
				headlines[strCount] = story->getTitle();
				strCount++;
			}
			
		
			rootnode = rootnode->Parent();
			rootnode = rootnode->NextSibling();
			rootnode = rootnode->FirstChild();
			story->setDescription(rootnode->Value());
			if(storyExists==false){
				std::cout<< story->getDescription() <<std::endl;
				a_file << story->getDescription();
				a_file << "\n";
			}
			
			rootnode = rootnode->Parent();
			rootnode = rootnode->NextSibling();
			rootnode = rootnode->FirstChild();
			story->setPubDate(rootnode->Value());
			if(storyExists==false){
				std::cout << story->getPubdate() <<std::endl;
				a_file << story->getPubdate();
				a_file << "\n";
			}
		
			rootnode = rootnode->Parent();
			rootnode = rootnode->NextSibling();
			
			rootnode = rootnode->FirstChild();
			story->setLink(rootnode->Value());
			if(storyExists==false){
				//std::cout<< story->getLink() << std::endl;
				a_file << story->getLink();
				a_file << "\n";
				a_file << "\n";
				printf("\n");
			}
			
			rootnode = rootnode->Parent();
			
			rootnode = rootnode->Parent();
			rootnode = rootnode->NextSibling();
			delete story;
			storyExists = false;
			
		}
	}

	pageSwitch++;
	if(pageSwitch>3){
		pageSwitch = 0;
		soundFlag=true;
	}
	a_file.close();
	Sleep(100000);
  }
	
  return 0;
}

