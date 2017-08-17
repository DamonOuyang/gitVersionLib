#include "PixmapMgr.h"
#include "lang_setting_helper.h"
#include "DirMgr.h"
#include "filetools.h"
#include <string>
using namespace std;
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>
using boost::property_tree::ptree;
using namespace boost;

const char* m_langNameList_pix[] = {
    "Pixmap",
    "German",
    "Dutch",
    "English",
    "Swedish",
    "French",
    "Hungarian",
    "Italian",
    "Danish",
    "Russian",
    "Polish",
    "Spanish",
    "Turkish",
    "Chinese",
    "Norwegian",
    "Finnish",
    "Greek",
    "Tschegish",
    "Ukrainian",
    "Chinese (Traditional)",
    "Albanian",
    "Arabic",
    "Bulgarian",
    "Catalan",
    "Croatian",
    "Czech",
    "Estonian",
    "Filipino",
    "Galician",
    "Hebrew",
    "Hindi",
    "Indonesian",
    "Japanese",
    "Korean",
    "Latvian",
    "Lithuanian",
    "Maltese",
    "Portuguese",
    "Romanian",
    "Serbian",
    "Slovak",
    "Slovenian",
    "Thai",
    "Vietnamese"
};

const std::string PixmapMgr::m_invalidGroupName = "~~invalid_group";

PixmapMgr::PixmapMgr(void)
	: m_defLang(e_pixmap),
	  m_isInit(false),
	  m_path("")
{
	if(!initDefault())
	{
		printf("%s\n","pix init err");
	}
}

PixmapMgr::~PixmapMgr(void)
{
}

bool PixmapMgr::init(const std::string & fn)
{
	if (!m_isInit)
	{
		m_path = fn;
		m_isInit =  parse(fn);
	}
	return m_isInit;
}

bool PixmapMgr::reInit(const std::string & fn)
{
	m_path = fn;
	m_isInit =  parse(fn);

	return m_isInit;
}


void PixmapMgr::getLangList(std::vector<int> & lang_list) const
{
	for(LangList_t::const_iterator iter = m_langList.begin(); iter != m_langList.end(); ++iter)
		lang_list.push_back(iter->first);
}

void PixmapMgr::getSupportLangList(std::vector<int> & lang_list) const
{	 
	for( vector<int>::const_iterator iter = m_supportLangList.begin();
		 iter != m_supportLangList.end();
		 iter ++)
	{
		lang_list.push_back( *iter );
	}
}

void PixmapMgr::setSupportLangList(std::vector<int> & lang_list)
{	 
	m_supportLangList.clear();
	for( vector<int>::const_iterator iter = lang_list.begin();
		iter != lang_list.end();
		iter ++)
	{		
		m_supportLangList.push_back( *iter );
	}	 
}

bool PixmapMgr::getText(const std::string & text_id,
					  std::string & text, 
					  int lang) const
{
	if(lang == e_unknown) lang = m_defLang;
	bool result = getText(text_id, m_invalidGroupName, text, lang);

	if(!result) {
		// Find in all groups
		LangList_t::const_iterator lliter = m_langList.find(lang);
		if(lliter != m_langList.end()) {
			const GroupList_t & gl = lliter->second;
			for(GroupList_t::const_iterator gliter = gl.begin(); gliter != gl.end(); ++gliter) {
				if((gliter->first != m_invalidGroupName) && getText(text_id, gliter->first, text, lang)) {
					result = true;
					break;
				}
			}
		}
	}

	return result;
}

bool PixmapMgr::getText(const std::string & text_id,
					  const std::string & group_id, 
					  std::string & text, 
					  int lang) const
{
	LangList_t::const_iterator lliter = m_langList.find(lang);
	if(lliter != m_langList.end()) {
		const GroupList_t & gl = lliter->second;
		GroupList_t::const_iterator gliter = gl.find(group_id);
		if(gliter != gl.end()) {
			const TransUnitList_t & tul = gliter->second;
			TransUnitList_t::const_iterator tuliter = tul.find(text_id);
			if(tuliter != tul.end()) {
				text = tuliter->second;
				return true;
			}
		}
	}
	return false;
}

bool PixmapMgr::getText(const std::string & text_id,
					  std::wstring & wtext, 
					  int lang) const
{
	if(lang == e_unknown) lang = e_english;
	string text;
	if(getText(text_id, text, lang)) {
		wtext.clear();
		utf8_to_utf16(text, wtext);
		return true;
	}
	return false;
}

std::wstring PixmapMgr::getText( const std::string & text_id,	 int lang ) const
{
	wstring ret;
	if(!getText(text_id,ret,lang))
	{
		if(!getText(text_id,ret,e_english))
		{
			utf8_to_utf16(text_id, ret);
		}
	}
	return ret;
}

bool PixmapMgr::getText(const std::string & text_id,
					  const std::string & group_id, 
					  std::wstring & wtext, 
					  int lang) const
{
	string text;
	if(getText(text_id, group_id, text, lang)) {
		wtext.clear();
		utf8_to_utf16(text, wtext);
		return true;
	}
	return false;
}

bool PixmapMgr::getGroupText(const std::vector<std::string> & group_id,
					       std::vector<std::string> & text,
					       int lang) const
{
	if(lang == e_unknown) lang = m_defLang;
	LangList_t::const_iterator lliter = m_langList.find(lang);
	if(lliter == m_langList.end())
		return false;
	
	for(vector<string>::size_type i = 0; i < group_id.size(); ++i) {
		const GroupList_t & gl = lliter->second;
		GroupList_t::const_iterator gliter = gl.find(group_id[i]);
		if(gliter != gl.end()) {
			const TransUnitList_t & tul = gliter->second;
			for(TransUnitList_t::const_iterator tuliter = tul.begin(); tuliter != tul.end(); ++tuliter)
				text.push_back(tuliter->second);
		}
	}
	return true;
}

bool PixmapMgr::getGroupText(const std::vector<std::string> & group_id,
					       std::vector<std::wstring> & wtext,
					       int lang) const
{
	vector<string> text;
	if(getGroupText(group_id, text, lang)) {
		wstring tmp;
		for(vector<string>::size_type i = 0; i < text.size(); ++i) {
			utf8_to_utf16(text[i], tmp);
			wtext.push_back(tmp);
		}
	}
	return true;
}

bool PixmapMgr::utf8_to_utf16(const std::string & source, std::wstring & target)
{
	unsigned long c;
	size_t extra_bytes;

	for(string::size_type i = 0; i < source.size(); NULL) {
		c = static_cast<unsigned long>(source[i++] & 0xFFUL);

		if((c & 0x80UL) == 0UL) {
			//1 octet
			target.push_back(static_cast<wchar_t>(c));
			continue;
		} else if((c & 0xE0UL) == 0xC0UL) {
			//2 octet
			c -= 0xC0UL;
			extra_bytes = 1;
		} else if((c & 0xF0UL) == 0xE0UL) {
			// 3 octet
			c -= 0xE0UL;
			extra_bytes = 2;
		} else if((c & 0xF8UL) == 0xF0UL) {
			// 4 octet
			c -= 0xF0UL;
			extra_bytes = 3;
		} else {
			//5 or 6 octets cannot be converted to UTF-16
			return false;
		}

		while(extra_bytes) {
			if(source[i] == 0) return 0; //unexpected end of string
			if((source[i] & 0xC0UL) != 0x80UL) return 0; //illegal trailing byte

			c <<= 6;
			c += static_cast<unsigned long>(source[i++] & 0x3FUL);

			--extra_bytes;
		}

		if(c < 0x10000UL) {
			//value between 0xD800 and 0xDFFF are preserved for UTF-16 pairs
			if(c >= 0xD800UL && c <= 0xDFFFUL) return false;
			target.push_back(static_cast<wchar_t>(c));
		} else {
			c -= 0x10000UL;

			//value greater than 0x10FFFF, illegal UTF-16 value;
			if(c >= 0x100000UL) return false; 

			target.push_back(static_cast<wchar_t>(0xD800UL + (c >> 10)));
			target.push_back(static_cast<wchar_t>(0xDC00UL + (c & 0x3FFUL)));
		}
	}

	return true;
}

bool PixmapMgr::utf16_to_utf8(const std::wstring & source, std::string & target)
{
	unsigned long FirstByteMasks[4] = {0x00UL, 0xC0UL, 0xE0UL, 0xF0UL};
	char buf[5];
	char * p;
	unsigned long c;
	size_t extra_bytes;

	for(wstring::size_type i = 0; i < source.size(); ++i) {
		c = static_cast<unsigned long>(source[i++] & 0xFFFFUL);

		//convert UTF-16 literal to UCS-4
		if(c >= 0xD800UL && c <= 0xDBFFUL) {
			c &= 0x03FFUL;
			c <<= 10;

			unsigned long c1 = static_cast<unsigned long>(source[i++] & 0xFFFFUL);

			if(c1 >= 0xDC00UL && c1 <= 0xDFFFUL)
				c += c1 & 0x03FFUL;
			else
				return false;
		} else if(c >= 0xDC00UL && c <= 0xDFFFUL) {
			return false;
		}

		//convert UCS-4 literal to UTF-8
		if(c < 0x80UL) extra_bytes = 0;
		else if(c < 0x800UL) extra_bytes = 1;
		else if(c < 0x10000UL) extra_bytes = 2;
		else extra_bytes = 3;

		buf[extra_bytes + 1] = '\0';
		p = &buf[extra_bytes];
		switch(extra_bytes) {
		case 3:
			*p-- = (char)((c | 0x80UL) & 0xBFUL);
			c >>= 6;
		case 2:
			*p-- = (char)((c | 0x80UL) & 0xBFUL);
			c >>= 6;
		case 1:
			*p-- = (char)((c | 0x80UL) & 0xBFUL);
			c >>= 6;
		case 0:
			*p = (char)(c | FirstByteMasks[extra_bytes]);
		}

		target += buf;
	}

	return true;
}

bool PixmapMgr::parseSupportLangs(const string &fn)
{
	ptree pt;
	try
	{
		read_xml(fn,pt, boost::property_tree::xml_parser::no_comments);

		//Read the default language
        string s=pt.get<string>("Jetinno.LangMgr.<xmlattr>.default-language","English");
		setDefaultLang(getLangType(s));
		setCurrentLang(getLangType(s));

		//Read the support language
        const optional<ptree &> & lbody = pt.get_child_optional("Jetinno.LangMgr.body");
		if( lbody )
		{
			m_supportLangList.clear();
			for(ptree::const_iterator it = lbody->begin(); it != lbody->end(); ++it)
			{
				if( it->first=="support-lang" )
				{
					PixmapMgr::LanguageType lang=getLangType(it->second.data());
					if( lang!=e_unknown )
					{
						if( m_supportLangList.end()==
							find(m_supportLangList.begin(),m_supportLangList.end(),lang) )
						{
							m_supportLangList.push_back(lang);
						}
					}
				}
			}
		}
	}
	catch(boost::exception &)
	{
		return false;
	}
	return true;
}

bool PixmapMgr::parseBody(const string &fn, string &version, PixmapMgr::LangList_t &langList)
{
	version="";
	langList.clear();

	ptree pt;
	try
	{
		read_xml(fn,pt, boost::property_tree::xml_parser::no_comments);

		//Read the language translation text
        version=pt.get<string>("Jetinno.LangMgr.xliff.<xmlattr>.version","1.0");
		langList.clear();
        const optional<ptree &>& xliff = pt.get_child_optional("Jetinno.LangMgr.xliff");
		if( xliff )
		{
			for(ptree::iterator xit = xliff->begin(); xit != xliff->end(); ++xit)
			{
				if( xit->first=="file" )
				{
					string langStr = xit->second.get<string>("<xmlattr>.target-language","");
					PixmapMgr::LanguageType lang=getLangType(langStr);
					if( e_unknown!=lang )
					{
						GroupList_t groupList;
						const optional<ptree &>& body = xit->second.get_child_optional("body");
						for(ptree::iterator git = body->begin(); git != body->end(); ++git)
						{
							if( git->first=="group" )
							{
								string groupId = git->second.get<string>("<xmlattr>.id","");
								const optional<ptree &>& tu = git->second.get_child_optional("");
								TransUnitList_t tulist;
								for(ptree::iterator tuit = tu->begin(); tuit != tu->end(); ++tuit)
								{
									if( tuit->first=="trans-unit" )
									{
										string id=tuit->second.get<string>("<xmlattr>.id","");
										string target=tuit->second.get<string>("target");
										tulist[id]=target;
									}
								}
								groupList[groupId]=tulist;
							}
						}
						langList[lang]=groupList;
					}
				}
			}
		}

	}
	catch(boost::exception &)
	{
		return false;
	}

	return true;
}

bool PixmapMgr::parse(const std::string &fn)
{
	bool ret;

	string path=fn;
	string::size_type idx=path.find_last_of("/");
	if (idx==string::npos)
	{
		idx=path.find_last_of("\\");
	}
	assert(idx!=string::npos);
	path.erase(idx+1);
    path+="pixmap_setting.xml";

	ret=::myFileExists(path);
    if (ret) //file "pixmap_setting.xml" exist
	{
        //read "pixmap_setting.xml"
		ret=setLangInfoFromLangSetting(path);
	}

	if (!ret)
	{
        //read old "pixmap.xml"
		ret=parseSupportLangs(fn);
	}

	ret=parseBody(fn,m_version,m_langList);
	return ret;
}

PixmapMgr::LanguageType PixmapMgr::getLangType(const std::string & name)
{
	for(int i = 0; i < (sizeof(m_langNameList_pix) / sizeof(m_langNameList_pix[0])); ++i) {
                if(0 == strcmp(m_langNameList_pix[i],name.c_str()))
			return LanguageType(i);
	}

	return e_unknown;
}

const char* PixmapMgr::getLangName(int lang)
{	
	if (lang == e_unknown)
	{
		return "UnKnown";
	}
	return m_langNameList_pix[lang];
}	

int PixmapMgr::getLangID( std::string lang )
{
	int ID = 0;
	for (;ID < sizeof(m_langNameList_pix) / sizeof(m_langNameList_pix[0]);++ID)
	{
		if (string(m_langNameList_pix[ID]) == lang)
		{
			return ID;
		}
	}
	return ID;
}

bool PixmapMgr::doUpdate(const string &oldVenduiDir)
{
	string path;
	::getRunningPath(path);

	string machineConfigDirName = DirMgr::getMachineConfigDirName();
	path += machineConfigDirName;

    //deal with "pixmap_setting.xml"
	string old_path = oldVenduiDir + machineConfigDirName;
    if (!::myFileExists(path + "/pixmap_setting.xml"))
	{
		::myCreatePath(path);
        if (!::myFileExists(old_path + "/pixmap_setting.xml"))
		{
            bool ret=reInit(old_path + "/pixmap.xml");
			if (ret)
			{
				int cuiDefaultLang=getDefaultLang();

				vector<int> ouiSupportLangs;
				getSupportLangList(ouiSupportLangs);
				if (PixmapMgr::e_english!=cuiDefaultLang || (!ouiSupportLangs.empty()))
				{
					LangSettingInfo_t langSettingInfo;

					langSettingInfo.cuiDefaultLang=cuiDefaultLang;
					langSettingInfo.ouiSupportLangs=ouiSupportLangs;

                    LangSettingHelper::set_lang_setting_info(langSettingInfo, old_path+"/pixmap_setting.xml");
				}
			}
		}

        if (::myFileExists(old_path + "/pixmap_setting.xml"))
		{
            ::myCopyFile(old_path + "/pixmap_setting.xml", path + "/pixmap_setting.xml");
		}
	}

    if(!::myFileExists(path + "/pixmap.xml"))
	{
		::myCreatePath(path);
        ::myCopyFile(oldVenduiDir + machineConfigDirName + "/pixmap.xml",
            path + "/pixmap.xml");
	}
	return true;
}

bool PixmapMgr::update(const string& oldVenduiDir,const string& oldVersion,const UpdatePackageInfo & info)
{
	return doUpdate(oldVenduiDir);
}

bool PixmapMgr::isEastLang(PixmapMgr::LanguageType langtype)
{
    if (langtype == PixmapMgr::e_chinese ||
        langtype == PixmapMgr::e_chineseTraditional ||
        langtype == PixmapMgr::e_arabic ||
        langtype == PixmapMgr::e_hindi  ||
        langtype == PixmapMgr::e_filipino ||
        langtype == PixmapMgr::e_indonesian ||
        langtype == PixmapMgr::e_japanese ||
        langtype == PixmapMgr::e_korean   ||
        langtype == PixmapMgr::e_thai     ||
        langtype == PixmapMgr::e_vietnamese
		)
	{
		return true;
	}
	return false;
}

bool PixmapMgr::initDefault()
{
	if (!m_isInit)
	{
		string path;
		getRunningPath(path);
		path += DirMgr::getMachineConfigDirName();
        string pathFile = path+"/pixmap.xml";

		

        m_isInit = singleton<PixmapMgr>::instance().init(pathFile);
	}
	return m_isInit;
}

bool PixmapMgr::setLangInfoFromLangSetting(const string &fn)
{
	int cuiDefaultLang;
	SupportLangs_t ouiSupportLangs;
	bool ret=LangSettingHelper::get_cui_default_language_oui_support_languages(cuiDefaultLang,ouiSupportLangs,fn);
	if (ret)  
	{ 
		setCurrentLang(cuiDefaultLang);
		setDefaultLang(cuiDefaultLang);
		setSupportLangList(ouiSupportLangs);
	}
	return ret;
}

QPixmap PixmapMgr::getPixmapFromXml(const char* pTextId)
{
    PixmapMgr::LanguageType pix = e_pixmap;
    QString tmp = getLangTypeText(pix, pTextId);
    QPixmap tmpPix = QPixmap(getLangTypeText(pix, pTextId));
    return tmpPix;
}

QString PixmapMgr::getLangTypeText(PixmapMgr::LanguageType lang, const char *pTextId)
{
    QString tmp =  QString::fromStdWString(getText( pTextId ,lang));
    if(tmp == "")
    {
        tmp =  QString::fromStdWString(getText(pTextId, PixmapMgr::e_pixmap));
    }
    return tmp;
}
