#include "stdafx.h"
#include "Formater.h"

void replaceAll(std::string& str, const std::string& from, const std::string& to) {
	if(from.empty())
		return;
	size_t start_pos = 0;
	while((start_pos = str.find(from, start_pos)) != std::string::npos) {
		str.replace(start_pos, from.length(), to);
		start_pos += to.length(); // In case 'to' contains 'from', like replacing 'x' with 'yx'
	}
}

Formater::Formater()
{

}

void Formater::Go()
{
	this->DeleteHooks();
	this->InsertInclude();
	//this->RetreiveRuntime();
	cout << "---------- All Done ----------" << endl;
}

void Formater::DeleteHooks()
{
	cout << "---------- Removing Hooks_*.cpp files ----------" << endl;
	path currentPath(current_path());
	try
	{
		if (exists(currentPath))
		{

			if (is_directory(currentPath))
			{
				PathVector files;

				copy(directory_iterator(currentPath), directory_iterator(), back_inserter(files));

				sort(files.begin(), files.end());
  
				for (auto it (files.begin()); it != files.end(); ++it)
				{
					if( it->filename().string().find("Hooks_") != string::npos && it->extension() != ".h" )
					{
						string fileName = it->filename().string();
						cout << "Removing " << it->filename().string() << endl;
						remove(it->filename().c_str());
					}
				}
			 }
		}
  }
  catch (const filesystem_error& ex)
  {
    cout << ex.what() << '\n';
  }
}

void Formater::InsertInclude()
{
	cout << "---------- Inserting includes ----------" << endl;
	path currentPath(current_path());

	try
	{
		if (exists(currentPath))    
		{

			if (is_directory(currentPath))      
			{
             
				PathVector files;                                

				copy(directory_iterator(currentPath), directory_iterator(), back_inserter(files));

				sort(files.begin(), files.end());             
                                              
  
				for (PathVector::const_iterator it (files.begin()); it != files.end(); ++it)
				{
					cout << "Writing in " << it->filename().string() << endl;
					string write;
					ifstream is(it->filename().string());
					string line;
					while( getline(is,line) )
					{
						write.append(line).append("\n");
					}

					ofstream os(it->filename().string());
					if(write.find("stdafx.h") == std::string::npos)
					{
						if( it->extension() == ".cpp" )
						{
							os << "#include \"stdafx.h\"\n";
						}
					}
					os << write;
				}
			}
		}
	  }
	  catch (const filesystem_error& ex)
	  {
		cout << ex.what() << '\n';
	  }
}