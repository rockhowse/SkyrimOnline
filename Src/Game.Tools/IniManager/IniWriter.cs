using IniParser;
using IniParser.Model;
using log4net;

#region

using System;
using System.Reflection;

#endregion

/* * * * * * * * * * * * * * * * * * *
 * By Konrad Janczarek nick Nerus87  *
 * For Skyrime Online project        *
 *                                   *
 *      Creating ini files           *
 *                                   *
 * * * * * * * * * * * * * * * * * * */

namespace Game.Tools.IniManager
{
    public class IniWriter
    {
        private static IniParser.FileIniDataParser parser = null;
        private static readonly ILog Logger = LogManager.GetLogger(MethodBase.GetCurrentMethod().DeclaringType);
        private static string path;
        private IniData data = null;

        private KeyData keyData = null;
        private SectionData sectionData = null;

        /// <summary>
        ///     EN: Constructor of class to create instance and set path to save file
        /// </summary>
        /// <param name="filePath">Path to file</param>
        /// <example>Example: how to create instance</example>
        /// <code>IniWriter("folder/filename.ini")</code>
        public IniWriter(string filePath)
        {
            if (filePath != null)
            {
                path = filePath;

                if (data == null)
                {
                    data = new IniData();
                }

                parser = new FileIniDataParser();
            }
        }

        /*
        public IniWriter(IniData data)
        {

            if (data == null)
            {
                this.data = new IniData();
            }
            else
            {
                this.data = data;
            }

            parser = new FileIniDataParser();

        }*/

        /// <summary>
        ///     EN: Add section if section not exist and select, otherwise only select.
        /// </summary>
        /// <param name="section">Section name</param>
        /// <example>Example: How to add and select section</example>
        /// <code>AddAndSelectSection("General")</code>
        public void addAndSelectSection(string section)
        {
            if (data != null)
            {
                if (data.Sections.GetSectionData(section) != null)
                {
                    // Get section from data
                    sectionData = data.Sections.GetSectionData(section);
                }
                else
                {
                    // Creating section
                    data.Sections.AddSection(section);
                    // Get section from data
                    sectionData = data.Sections.GetSectionData(section);
                }
            }
        }

        /// <summary>
        ///     EN: Add section if section not exist and select, otherwise only select.
        ///     Add comment to section if comment not exist, otherwise delete old comment and add new.
        /// </summary>
        /// <param name="section">Section name to add</param>
        /// <param name="comment">Section comment</param>
        /// <example>Example: How to add section with comment and select this section</example>
        /// <code>AddAndSelectSection("General", "This is a general section")</code>
        public void addAndSelectSection(string section, string comment)
        {
            if (data != null)
            {
                if (data.Sections.GetSectionData(section) != null)
                {
                    // Get section from data
                    sectionData = data.Sections.GetSectionData(section);
                }
                else
                {
                    // Creating section
                    data.Sections.AddSection(section);
                    // Get section from data
                    sectionData = data.Sections.GetSectionData(section);
                }

                if (comment != null && !comment.Equals(""))
                {
                    if (sectionData.Comments.Count > 0)
                    {
                        sectionData.Comments.Clear();
                    }

                    sectionData.Comments.Add(comment);
                }
            }
        }

        /// <summary>
        ///     EN: Add key to selected section with key value
        /// </summary>
        /// <param name="key">Key name to add</param>
        /// <param name="value">Key value to set</param>
        /// <example>Example: How to add key with value to selected section</example>
        /// <code>addKeyToSelectedSection("name", "Igor")</code>
        public void addKeyToSelectedSection(string key, string value)
        {
            if (sectionData != null)
            {
                if (sectionData.Keys.GetKeyData(key) != null)
                {
                    // Get key from Section
                    keyData = sectionData.Keys.GetKeyData(key);
                }
                else
                {
                    // Adding key to Sectrion
                    sectionData.Keys.AddKey(key);
                    // Get key from Section
                    keyData = sectionData.Keys.GetKeyData(key);
                }

                if (value != null)
                {
                    // Set value to key
                    keyData.Value = value;
                }
            }
        }

        /// <summary>
        ///     EN: Add key to selected section with key value and comment
        /// </summary>
        /// <param name="key">Key name to add</param>
        /// <param name="value">Value to set</param>
        /// <param name="comment">Comment to set</param>
        /// <example>Example: How to add key with value and comment to selected section</example>
        /// <code>addKeyToSelectedSection("name", "My best frend" ,"Igor")</code>
        public void addKeyToSelectedSection(string key, string value, string comment)
        {
            if (sectionData != null)
            {
                if (sectionData.Keys.GetKeyData(key) != null)
                {
                    // Get key from Section
                    keyData = sectionData.Keys.GetKeyData(key);
                }
                else
                {
                    // Adding key to Sectrion
                    sectionData.Keys.AddKey(key);
                    // Get key from Section
                    keyData = sectionData.Keys.GetKeyData(key);
                }

                if (comment != null && !comment.Equals(""))
                {
                    if (keyData.Comments.Count > 0)
                    {
                        keyData.Comments.Clear();
                    }

                    keyData.Comments.Add(comment);
                }

                if (value != null)
                {
                    // Set value to key
                    keyData.Value = value;
                }
            }
        }

        /*
        /// <summary>
        /// EN: Create key with value in section
        /// </summary>
        /// <param name="section">Section name</param>
        /// <param name="key">Key name</param>
        /// <param name="value">Key value</param>
        public void setValue(string section, string key, string value)
        {

            if (section != null)
            {

                SectionData Section = null;

                if (data.Sections.GetSectionData(section) != null)
                {
                    // Get section from data
                    Section = data.Sections.GetSectionData(section);
                }
                else
                {
                    // Creating section
                    data.Sections.AddSection(section);
                    // Get section from data
                    Section = data.Sections.GetSectionData(section);
                }

                if (key != null)
                {

                    KeyData Key = null;

                    if (Section.Keys.GetKeyData(key) != null)
                    {
                        // Get key from Section
                        Key = Section.Keys.GetKeyData(key);
                    }
                    else
                    {
                        // Adding key to Sectrion
                        Section.Keys.AddKey(key);
                        // Get key from Section
                        Key = Section.Keys.GetKeyData(key);
                    }

                    if (value != null)
                    {
                        // Set value to key
                        Key.Value = value;
                    }
                }
            }
        }

        /// <summary>
        /// EN: TODO
        /// </summary>
        /// <param name="section"></param>
        /// <param name="sectionComment"></param>
        /// <param name="key"></param>
        /// <param name="keyComment"></param>
        /// <param name="value"></param>
        public void setValue(string section, string sectionComment, string key, string keyComment, string value)
        {

            if (section != null)
            {

                SectionData Section = null;

                if (data.Sections.GetSectionData(section) != null)
                {
                    // Get section from data
                    Section = data.Sections.GetSectionData(section);
                }
                else
                {
                    // Creating section
                    data.Sections.AddSection(section);
                    // Get section from data
                    Section = data.Sections.GetSectionData(section);
                }

                if (sectionComment != null && !sectionComment.Equals(""))
                {
                    Section.Comments.Add(sectionComment);
                }

                if (key != null)
                {

                    KeyData Key = null;

                    if (Section.Keys.GetKeyData(key) != null)
                    {
                        // Get key from Section
                        Key = Section.Keys.GetKeyData(key);
                    }
                    else
                    {
                        // Adding key to Sectrion
                        Section.Keys.AddKey(key);
                        // Get key from Section
                        Key = Section.Keys.GetKeyData(key);
                    }

                    if (keyComment != null && !keyComment.Equals(""))
                    {
                        Key.Comments.Add(keyComment);
                    }

                    if (value != null)
                    {
                        // Set value to key
                        Key.Value = value;
                    }
                }
            }
        }

        /// <summary>
        /// EN: TODO
        /// </summary>
        /// <param name="section"></param>
        /// <param name="key_value_grupe">Group of keys and values</param>
        public void SetValue(string section, Dictionary<string, string> keyGroup)
        {

            if (section != null)
            {
                SectionData Section = null;

                try
                {
                    // Get section from data
                    Section = data.Sections.GetSectionData(section);
                }
                catch
                {
                    // Creating section
                    data.Sections.AddSection(section);
                    // Get section from data
                    Section = data.Sections.GetSectionData(section);
                }

                if (Section != null && keyGroup != null && keyGroup.Count > 0)
                {

                    KeyData Key = null;

                    foreach (KeyValuePair<string, string> pair in keyGroup)
                    {
                        try
                        {
                            // Get key from Section
                            Key = Section.Keys.GetKeyData(pair.Key);
                        }
                        catch
                        {
                            // Adding key to Sectrion
                            Section.Keys.AddKey(pair.Key);
                            // Get key from Section
                            Key = Section.Keys.GetKeyData(pair.Key);
                        }

                        if (Key != null && pair.Value != null)
                        {
                            // Add value to key
                            Key.Value = pair.Value;
                        }

                    }

                }

            }

        }
        */

        /// <summary>
        ///     EN: Save ini data to file
        /// </summary>
        /// <param name="filePath">file path</param>
        /// <returns>true if file saved, false otherwise</returns>
        /// <example>Example: how to save file</example>
        /// <code>if(SaveFile()) then...</code>
        public bool SaveFile()
        {
            bool result = false;

            if (path != null && data != null)
            {
                try
                {
                    parser.WriteFile(path, data);
                    result = true;
                }
                catch (Exception ex)
                {
                    Logger.Error(ex.Message);
                    result = false;
                }
            }

            if (result)
            {
                data = null;
            }

            return result;
        }

        /*
        /// <summary>
        /// EN: Return IniData
        /// WARNING if data saved to file data = null, use getData() before save file, but when save fail data != null
        /// </summary>
        /// <returns>IniData or null</returns>
        public IniData getData()
        {
            return data;
        }
        */
    }
}