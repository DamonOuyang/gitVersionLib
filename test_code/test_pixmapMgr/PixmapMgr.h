#ifndef	__PIXMPMGR_H__
#define __PIXMPMGR_H__

#include <singleton.h>
#include <iupdate.h>
#include <vector>
#include <string>
#include <map>
#include <QPixmap>
using namespace std;
#include <boost/noncopyable.hpp>

class PixmapMgr : public IUpdate, boost::noncopyable
{
    friend class singleton<PixmapMgr>;

public:
	typedef enum LanguageType
	{
		e_unknown = -1,
        e_pixmap = 0,
        e_german,
        e_dutch,
        e_english,
        e_swedish,
        e_french,
        e_hungarian,
        e_italian,
        e_danish,
        e_russian,
        e_polish,
        e_spanish,
        e_turkish,
        e_chinese,
        e_norwegian,
        e_finnish,
        e_greek,
        e_tschegish,
        e_ukrainian,
        e_chineseTraditional,
        e_albanian,
        e_arabic,
        e_bulgarian,
        e_catalan,
        e_croatian,
        e_czech,
        e_estonian,
        e_filipino,
        e_galician,
        e_hebrew,
        e_hindi,
        e_indonesian,
        e_japanese,
        e_korean,
        e_latvian,
        e_lithuanian,
        e_maltese,
        e_portuguese,
        e_romanian,
        e_serbian,
        e_slovak,
        e_slovenian,
        e_thai,
        e_vietnamese,
        e_lastLanguage
	}langType;

	static const unsigned short MAX_SUPPORT_LANG_LEN=3;

protected:
	/**@name Trans-unit list, <trans-unit ID, traget>
	 */
	typedef std::map<std::string, std::string>				TransUnitList_t;

	/**@name Group list, <group ID, trans-unit list>
	 */
	typedef std::map<std::string, TransUnitList_t>			GroupList_t;

	/**@name Language list, <language type, group list>
	 */
	typedef std::map<int, GroupList_t>						LangList_t;

public:
	/**Constructor
	 */
    PixmapMgr(void);

	/**Destructor
	 */
    ~PixmapMgr(void);

protected:
	/**Clear all
	 */
	void clear(void)
	{ m_langList.clear(); }

	//load from /vendui/machine/lang.xml
	bool initDefault();

	bool init(
		const std::string & fn
	);

	bool reInit(
		const std::string & fn
		);

	/**Get the language list in the language manager
	 */
	void getLangList(
		std::vector<int> & lang_list
	) const;

	/**Get the support language list in the language manager
	 */
	void getSupportLangList(std::vector<int> & lang_list) const;
	void setSupportLangList(std::vector<int> & lang_list) ;

	/**Set default language
	 */
	void setDefaultLang(
		int lang
	) { m_defLang = lang; }

	/**Get default language
	 */
	int getDefaultLang(void) const { return m_defLang; }

	/** get and set current language
	*/
	void setCurrentLang(int lang)
	{
		m_curLang = lang;
	}
	int  getCurrentLang() const 
	{
		return m_curLang;
	}

	string getVersion() const {return m_version;}
	bool isInit() const { return m_isInit;}

	bool setLangInfoFromLangSetting(const string &fn);

	/**Get text string for a specified language
	 */
	bool getText(
		const std::string & text_id,		///< The short ID for the text string
		std::string & text,					///< The text string
		int lang = e_unknown				///< Language ID. if e_unkown, use default language
	) const;

	/**Get text string for a specified language
	 */
	bool getText(
		const std::string & text_id,		///< The short ID for the text string
		std::wstring & wtext,				///< The text string
		int lang = e_unknown				///< Language ID. if e_unkown, use default language
	) const;

		/**Get text string for a specified language and text id
	 */
	std::wstring getText(
		const std::string & text_id,		///< The short ID for the text string		
		int lang = e_unknown				///< Language ID. if e_unkown, use default language
	) const;

	/**Get all text that belong to some specified groups
	 */
	bool getGroupText(
		const std::vector<std::string> & group_id,	///< The list of group's short ID
		std::vector<std::string> & text,			///< The list of text string for all groups
		int lang = e_unknown						///< Language ID. if e_unkown, use default language
	) const;

	/**Get all text that belong to some specified groups
	 */
	bool getGroupText(
		const std::vector<std::string> & group_id,	///< The list of group's short ID
		std::vector<std::wstring> & wtext,			///< The list of text string for all groups
		int lang = e_unknown						///< Language ID. if e_unkown, use default language
	) const;

	/**Get language name by it's type
	 */
	static const char* getLangName(
		int lang
	);
	
	static int getLangID(std::string lang);
	/**Get language type by it's name
	 */
	static LanguageType getLangType(
		const std::string & name
	);

	/**Convert UTF-8 to UTF-16
	 */
	static bool utf8_to_utf16(
		const std::string & source, 
		std::wstring & target
	);

	/**Convert UTF-16 to UTF-8
	 */
	static bool utf16_to_utf8(
		const std::wstring & source, 
		std::string & target
	);
	
	virtual bool update(
		const string& oldVenduiDir,const string& oldVersion,
		const UpdatePackageInfo & info
		);

	/*get the east lang
	*/
	static bool isEastLang(LanguageType langtype);
	
protected:
	/**Get a text string on a group in a specified language
	 */
	bool getText(
		const std::string & text_id, 
		const std::string & group_id, 
		std::string & text, 
		int lang
	) const;

	/**Get a text string on a group in a specified language
	 */
	bool getText(
		const std::string & text_id, 
		const std::string & group_id, 
		std::wstring & wtext, 
		int lang
	) const;

	/**Parse a language file
	 * Below is the description of the file's XML format. Most of them is borrowed from 
	 * the XLIFF specification, but we don't need to be compatible with it because we 
	 * just need a simple format. See the website for more info: http://www.oasis-open.org/
	 *
	 * <?xml version="1.0" encoding="UTF-8"?>
     * <Jetinno>
	 *		<LangMgr default-language="Dutch">
	 *		<body>
	 *			<support-lang>English</support-lang>
	 *			<support-lang>Dutch</support-lang>
	 *			<support-lang>German</support-lang>
	 *		</body>
	 *			<xliff version = "1.2">
	 *				<file target-language = "english">
	 *					<body>
	 *						<trans-unit id = "t1">
	 *					     <target>trans unit 1</target>
	 *						</trans-unit>
	 *						...
	 *						<group id = "group1">
	 *							<trans-unit id = "t2">
	 *								<target>trans unit 2</target>
	 *							</trans-unit>
	 *							...
	 *						</group>
	 *						<group id = "group2">
	 *							<trans-unit id = "t1">
	 *								<target>trans unit 1</target>
	 *							</trans-unit>
	 *							...
	 *						</group>
	 *						...
	 *					</body>
	 *				</file>
	 *				<file target-language = "chinese">
	 *					<body>
	 *						...
	 *					</body>
	 *				</file>
	 *				...
	 *			</xliff>
	 *		</LangMgr>
     *	</Jetinno>
	 * 
	 */
	bool parse(
		const std::string & fn
	);

private:
	bool parseSupportLangs(const string &fn);

	bool doUpdate(const string &oldVenduiDir);

    QString getLangTypeText(PixmapMgr::LanguageType lang, const char *pTextId);

protected:
	static bool parseBody(const string &fn, string &version, PixmapMgr::LangList_t &langList);

protected:
	int								m_defLang;				///< Default language
	int                             m_curLang;              ///< Current language
    std::vector<int>                m_supportLangList;      ///The support language in the machine
	LangList_t						m_langList;				///< Text list of all language
	static const std::string		m_invalidGroupName;		///< The name of invalid group
	string m_version;
public:
    QPixmap getPixmapFromXml(const char* pTextId);

protected:
	bool m_isInit;
	string m_path;
};

#endif	//__PIXMPMGR_H__

