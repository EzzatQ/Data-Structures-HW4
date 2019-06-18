//
//  Lecture_Info.hpp
//  Data Structures HW2
//
//  Created by Ezzat Qupty on 05/05/2019.
//  Copyright © 2019 Ezzat Qupty. All rights reserved.
//

#ifndef Lecture_Info_hpp
#define Lecture_Info_hpp


namespace DataStructures{
	class LectureInfo{
	public:
		int group;
		int hour;
		LectureInfo(int group, int hour):group(group), hour(hour){}
		
		~LectureInfo(){}
		
		LectureInfo(const LectureInfo& li){
			hour = li.hour;
			group = li.group;
		}
		LectureInfo& operator=(LectureInfo& li){
			hour = li.hour;
			group = li.group;
			return *this;
		}
		int getGroup() const {return group;}
        int getHour() const {return hour;}
	
		bool operator==(const LectureInfo& li) const {
			return group == li.group && hour == li.hour;
		}
		bool operator>(const LectureInfo& li) const {
			if(group > li.group) return true;
			else if(group == li.group && hour > li.hour) return true;
			else if(group == li.group && hour == li.hour && hour > li.hour) return true;
			else return false;
		}
		bool operator<(const LectureInfo& li) const {
			return !(operator>(li) || operator==(li));
		}
		bool operator>=(const LectureInfo& li) const {
			return operator>(li) || operator==(li);
		}
		bool operator<=(const LectureInfo& li) const {
			return operator<(li) || operator==(li);
		}
	};
}

#endif /* Lecture_Info_hpp */
