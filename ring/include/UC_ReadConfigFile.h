#pragma once
#include <iostream> //cerr
#include <fstream>
#include <vector>
#include <string>
#include <map>
#include <boost/lexical_cast.hpp>
#include <boost/algorithm/string/trim.hpp>

using namespace std;

class IniConfig
{
public:
    IniConfig(const char* iniFile)
	{
	    configs_[""]; 
		ifstream ifs(iniFile);
		if (!ifs)
		{
			cerr << "config file \"" << iniFile << "\" not found!";
			exit(-1);
		}

		vector<string> lines;
		string line;
		while (!ifs.eof())
		{
			getline(ifs, line);

			if (line.empty())
				continue;

			if (line.size() >= 1 && (line[0]=='#' || line[0]==';') )
				continue;

			lines.push_back(line);
		}

		for (vector<string>::iterator iter = lines.begin();
			iter != lines.end();
			++iter)
		{
			parse_line(*iter);
		}

		ifs.close();
	}
    template <typename T>
    T get(const std::string& section, const std::string& key)
    {
        check(section, key);
        return boost::lexical_cast<T>(configs_[section][key]);
    }
    const std::string& get(const std::string& section, const std::string& key)
    {
        check(section, key);
        return configs_[section][key];
    }

    template <typename T>
    T get(const std::string& key)
    {
        check("", key);
        return boost::lexical_cast<T>(configs_[""][key]);
    }
    const std::string& get(const std::string& key)
    {
        check("", key);
        return configs_[""][key];
    }

    void set(const std::string& section, const std::string& key, const std::string& newValue)
    {
        check(section, key);
        configs_[section][key] = newValue;
    }

private:
    IniConfig(const IniConfig&);
    IniConfig& operator=(const IniConfig& cfg);
    
	void parse_line(std::string& line)
	{
		boost::algorithm::trim(line);

		size_t pos = line.rfind(']');
		if (pos != string::npos)
		{
			assert(pos != 0);
			if (pos != 1) //not [] but [session], add a section
			{
				curSession_ = line.substr(1, pos-1);
				configs_[curSession_];
			}
			return;
		}
		else
		{
			pos = line.find('=');
			assert(pos != string::npos);

			string key, value;
			{
				char* pTrim;

				pTrim = &line[pos-1];
				while (*pTrim==' ' || *pTrim=='\t')
					pTrim--;
				key.assign(&line[0], ++pTrim);

				pTrim = &line[pos+1];
				while (*pTrim==' ' || *pTrim=='\t')
					pTrim++;
				value.assign(pTrim);
			}

			//cout << key << "=" << value << endl;
			configs_[curSession_].insert(KeyValue::value_type(key, value));
		}
	}
    inline void check(const std::string& section, const std::string& key)
    {
        assert (configs_.end()!=configs_.find(section) && configs_[section].end()!=configs_[section].find(key));
    }

    typedef std::map<std::string, std::string> KeyValue;

    std::map<std::string, KeyValue> configs_;
    std::string curSession_;
};

