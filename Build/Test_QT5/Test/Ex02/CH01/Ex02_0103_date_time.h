
#pragma once

class Ex02_0103_date_time : public ITestObject {
public:
	virtual int OnTest(int nArgNum, char **ppArgs) {
		cout_post_sz("Init", '-', 50);				OnTest_Init();				std::cout << std::endl;
		cout_post_sz("CurDateTime", '-', 50);		OnTest_CurDateTime();		std::cout << std::endl;
		cout_post_sz("Compare", '-', 50);			OnTest_Compare();			std::cout << std::endl;
		cout_post_sz("LeapYear", '-', 50);			OnTest_LeapYear();			std::cout << std::endl;
		cout_post_sz("DateFormat", '-', 50);		OnTest_DateFormat();		std::cout << std::endl;
		cout_post_sz("CustomDate", '-', 50);		OnTest_CustomDate();		std::cout << std::endl;
		cout_post_sz("TimeFormat", '-', 50);		OnTest_TimeFormat();		std::cout << std::endl;
		cout_post_sz("CustomTime", '-', 50);		OnTest_CustomTime();		std::cout << std::endl;
		cout_post_sz("WeekDay", '-', 50);			OnTest_WeekDay();			std::cout << std::endl;
		cout_post_sz("NumberOfDays", '-', 50);		OnTest_NumberOfDays();		std::cout << std::endl;
		cout_post_sz("Date Validity", '-', 50);		OnTest_DateValidity();		std::cout << std::endl;
		cout_post_sz("Days To From", '-', 50);		OnTest_DaysToFrom();		std::cout << std::endl;
		cout_post_sz("QDateTime", '-', 50);			OnTest_QDateTime();			std::cout << std::endl;
		cout_post_sz("Julian Day", '-', 50);		OnTest_JulianDay();			std::cout << std::endl;
		cout_post_sz("Julian Day2", '-', 50);		OnTest_JulianDay2();		std::cout << std::endl;
		cout_post_sz("UTC & Local", '-', 50);		OnTest_UTC_Local();			std::cout << std::endl;
		cout_post_sz("Unix Epoch", '-', 50);		OnTest_UnixEpoch();			std::cout << std::endl;
		std::cout << std::string(50, '-') << std::endl;
		return 0;
	}

	void OnTest_UnixEpoch() {
		QTextStream out(stdout);

		time_t t = time(0);
		out << t << endl;

		QDateTime dt;
		dt.setTime_t(t);
		out << dt.toString() << endl;

		QDateTime cd = QDateTime::currentDateTime();
		out << cd.toTime_t() << endl;
	}

	void OnTest_UTC_Local() {
		QTextStream out(stdout);

		QDateTime cdt = QDateTime::currentDateTime();

		out << "Universal datetime: " << cdt.toUTC().toString() << endl;
		out << "Local datetime: " << cdt.toLocalTime().toString() << endl;
	}

	void OnTest_JulianDay2() {
		QTextStream out(stdout);

		QDate bordate(1812, 9, 7);
		QDate slavdate(1805, 12, 2);

		QDate cd = QDate::currentDate();

		int j_today = cd.toJulianDay();
		int j_borodino = bordate.toJulianDay();
		int j_slavkov = slavdate.toJulianDay();

		out << "Days since Slavkov battle: " << j_today - j_slavkov << endl;
		out << "Days since Borodino battle: " << j_today - j_borodino << endl;
	}

	void OnTest_JulianDay() {
		QTextStream out(stdout);

		QDate cd = QDate::currentDate();

		out << "Gregorian date for today: " << cd.toString(Qt::ISODate) << endl;
		out << "Julian day for today: " << cd.toJulianDay() << endl;
	}

	void OnTest_QDateTime() {
		QTextStream out(stdout);
		QDateTime cdt = QDateTime::currentDateTime();

		out << "The current datetime is " << cdt.toString() << endl;
		out << "The current date is " << cdt.date().toString() << endl;
		out << "The current time is " << cdt.time().toString() << endl;
	}

	void OnTest_DaysToFrom() {
		QTextStream out(stdout);
		QDate dt(2015, 5, 11);
		QDate nd = dt.addDays(55);
		QDate xmas(2015, 12, 24);
		out << "55 days from " << dt.toString() << " is " << nd.toString() << endl;
		out << "There are " << dt.daysTo(xmas) << " days till Christmas" << endl;
	}

	void OnTest_DateValidity() {
		QTextStream out(stdout);
		QList<QDate> dates({ QDate(2015, 5, 11), QDate(2015, 8, 1), QDate(2015, 2, 30) });
		for (int i = 0; i < dates.size(); i++) {
			if (dates.at(i).isValid()) {
				out << "Date " << i + 1 << " is a valid date" << endl;
			}
			else {
				out << "Date " << i + 1 << " is not a valid date" << endl;
			}
		}
	}

	void OnTest_NumberOfDays() {
		QTextStream out(stdout);
		QList<QString> months;
		months.append("January");	months.append("February");		months.append("March");
		months.append("April");		months.append("May");			months.append("June");
		months.append("July");		months.append("August");		months.append("September");
		months.append("October");	months.append("November");		months.append("December");
		QDate dt1(2015, 9, 18);
		QDate dt2(2015, 2, 11);
		QDate dt3(2015, 5, 1);
		QDate dt4(2015, 12, 11);
		QDate dt5(2015, 1, 21);
		out << "There are " << dt1.daysInMonth() << " days in "	<< months.at(dt1.month() - 1) << endl;
		out << "There are " << dt2.daysInMonth() << " days in "	<< months.at(dt2.month() - 1) << endl;
		out << "There are " << dt3.daysInMonth() << " days in "	<< months.at(dt3.month() - 1) << endl;
		out << "There are " << dt4.daysInMonth() << " days in "	<< months.at(dt4.month() - 1) << endl;
		out << "There are " << dt5.daysInMonth() << " days in "	<< months.at(dt5.month() - 1) << endl;
		out << "There are " << dt1.daysInYear() << " days in year "	<< QString::number(dt1.year()) << endl;
	}

	// 월요일: 1, 일요일: 7
	void OnTest_WeekDay() {
		QTextStream out(stdout);

		QDate cd = QDate::currentDate();
		int wd = cd.dayOfWeek();

		out << "Today is " << QDate::shortDayName(wd) << endl;
		out << "Today is " << QDate::longDayName(wd) << endl;
	}

	void OnTest_CustomTime() {
		QTextStream out(stdout);

		QTime ct = QTime::currentTime();

		out << "The time is " << ct.toString("hh:mm:ss.zzz") << endl;
		out << "The time is " << ct.toString("h:m:s a") << endl;
		out << "The time is " << ct.toString("H:m:s A") << endl;
		out << "The time is " << ct.toString("h:m AP") << endl;
		out << "The version of Qt5 is " << qVersion() << endl;
	}

	void OnTest_TimeFormat() {
		QTextStream out(stdout);

		QTime ct = QTime::currentTime();

		out << "The time is " << ct.toString(Qt::TextDate) << endl;
		out << "The time is " << ct.toString(Qt::ISODate) << endl;
		out << "The time is " << ct.toString(Qt::SystemLocaleShortDate) << endl;
		out << "The time is " << ct.toString(Qt::SystemLocaleLongDate) << endl;
		out << "The time is " << ct.toString(Qt::DefaultLocaleShortDate) << endl;
		out << "The time is " << ct.toString(Qt::DefaultLocaleLongDate) << endl;
		out << "The time is " << ct.toString(Qt::SystemLocaleDate) << endl;
		out << "The time is " << ct.toString(Qt::LocaleDate) << endl;
	}

	/*
	Expression	Output
	d			The day as a number without a leading zero (1 to 31) 
	dd			The day as a number with a leading zero (01 to 31) 
	ddd			The abbreviated localized day name (e.g. 'Mon' to 'Sun'). Uses QDate::shortDayName(). 
	dddd		The long localized day name (e.g. 'Monday' to 'Sunday'). Uses QDate::longDayName(). 
	M			The month as a number without a leading zero (1 to 12) 
	MM			The month as a number with a leading zero (01 to 12) 
	MMM			The abbreviated localized month name (e.g. 'Jan' to 'Dec'). Uses QDate::shortMonthName(). 
	MMMM		The long localized month name (e.g. 'January' to 'December'). Uses QDate::longMonthName(). 
	yy			The year as two digit number (00 to 99) 
	yyyy		The year as four digit number. If the year is negative, a minus sign is prepended in addition. 
	*/
	void OnTest_CustomDate() {
		QTextStream out(stdout);

		QDate cd = QDate::currentDate();

		out << "Today is " << cd.toString("yyyy-MM-dd") << endl;
		out << "Today is " << cd.toString("yy/M/dd") << endl;
		out << "Today is " << cd.toString("d. M. yyyy") << endl;
		out << "Today is " << cd.toString("d-MMMM-yyyy") << endl;
	}

	void OnTest_DateFormat() {
		QTextStream out(stdout);

		QDate cd = QDate::currentDate();

		out << "Today is " << cd.toString(Qt::TextDate) << endl;
		out << "Today is " << cd.toString(Qt::ISODate) << endl;
		out << "Today is " << cd.toString(Qt::SystemLocaleShortDate) << endl;
		out << "Today is " << cd.toString(Qt::SystemLocaleLongDate) << endl;
		out << "Today is " << cd.toString(Qt::DefaultLocaleShortDate) << endl;
		out << "Today is " << cd.toString(Qt::DefaultLocaleLongDate) << endl;
		out << "Today is " << cd.toString(Qt::SystemLocaleDate) << endl;
		out << "Today is " << cd.toString(Qt::LocaleDate) << endl;
	}

	void OnTest_LeapYear() {
		QTextStream out(stdout);
		QList<int> years({ 2010, 2011, 2012, 2013, 2014, 2015, 2016 });

		foreach(int year, years) {
			if (QDate::isLeapYear(year)) {
				out << year << " is a leap year" << endl;
			}
			else {
				out << year << " is not a leap year" << endl;
			}
		}
	}

	void OnTest_Compare() {
		QTextStream out(stdout);

		QDate dt1(2015, 4, 5);
		QDate dt2(2014, 4, 5);

		if (dt1 < dt2) {
			out << dt1.toString() << " comes before "
				<< dt2.toString() << endl;
		}
		else {
			out << dt1.toString() << " comes after "
				<< dt2.toString() << endl;
		}
	}

	void OnTest_CurDateTime() {
		QTextStream out(stdout);

		QDate cd = QDate::currentDate();
		QTime ct = QTime::currentTime();

		out << "Current date is: " << cd.toString() << endl;
		out << "Current time is: " << ct.toString() << endl;
	}

	void OnTest_Init() {
		QTextStream out(stdout);

		QDate dt1(2015, 4, 12);						out << "The date is " << dt1.toString() << endl;
		QDate dt2;	dt2.setDate(2015, 3, 3);		out << "The date is " << dt2.toString() << endl;
		QTime tm1(17, 30, 12, 55);					out << "The time is " << tm1.toString("hh:mm:ss.zzz") << endl;
		QTime tm2; 	tm2.setHMS(13, 52, 45, 155);	out << "The time is " << tm2.toString("hh:mm:ss.zzz") << endl;
	}
};