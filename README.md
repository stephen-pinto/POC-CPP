
# All proof-of-concept projects

### It contains below projects merged into a single repository:


 1.  **PointyBoot** : 
  _A C# version of SpringBoot Depenedency management framework._
      
      - This is just a DI framework to solve DI for functions, properties and classes like how SpringBoot works. Needs more performance improvement.
      - The name derives from C#'s Sharp and SpringBoot's Boot = SharpBoot = PointyBoot :stuck_out_tongue_winking_eye:
      - Works with the primary use-case. Also contains performance tests in TestApp project.
      - **Based on:**  Plain C# with Reflection.
      - You can find the code for this whole project here: [PointyBoot](https://github.com/stephen-pinto/POC/tree/main/PointyBoot)


 2.  **CustomMemoryManager** : 
    _A C++ custom memory manager created in Qt developed around the idea of memory pooling with different memory requirements_
    
      - It's based on the concept of Memory pooling. It allocates a pool and the concept of allocation depends on the type of process requesting memory. From a very memory hungry process to a simple process requesting occasional memory. It can be configured from the allocator.
      - It works w.r.t primary use case.
      - **Based on:** Qt and C++.
      - You can find its code here: [CustomMemoryManager](https://github.com/stephen-pinto/POC/tree/main/CustomMemoryManager)


 3.  **SQLEditor** : 
    _A editor developed using the Qt framework (C++) for writing SQL files mainly for the Firebird database. At present only supports syntax highlighting and no intellisense_    	
      
      - This was started in the interest of having a better editor for firebird database than the currently available default editor. 
      - Its goal was to provide all intellisense and code highlighting which could be easily configurable. 
      - It would eventually also perform all its execution in a separate thread thus not freezing the actual client  and causing it to crash which is the biggest issue when using the default editor.
      - **Based on:** Qt and C++.
      - You can find its code here: [SQLEditor](https://github.com/stephen-pinto/POC/tree/main/SQLEditor)
    
    
4. **SftpClient** : 
  _A Qt application (C++) client for helping with SFTP file transfers. A basic application_
    
    - This is a simple sftp client which can be used to fetch files using the sftp protocol.
    - Lot of work pending to be done here. But basic transfer worked. 
    - **Based on:**  Qt and C++.
    - You can find its code here: [SftpClientProject](https://github.com/stephen-pinto/POC/tree/main/SftpClientProject)


5.  **ComCSharpInteropLibraries** : 
  _This solution is supposed to hold all interop libraries. At present it contains a ADO like client for Firebird DB based on COM (OLE)_
  
      - The goal of this project was to create a custom ADO like client for firebird getting all information about its DDF and other information and provide connection to .NET clients.
      - The idea is to use COM for its architecture.
      - It works when getting information about existing tables and running query.
      - **Based on:** VC++, ComponentObjectModel (OLE).
      - You can find its code here: [ComCSharpIteropLibraries](https://github.com/stephen-pinto/POC/tree/main/ComCSharpIteropLibraries)


6. **FSManagementApp** : 
  _A C++ app where I try to prepare a list of files in the FS_
  
      - An experimental project to collect a list of files and gather its distinction with MD5.
      - Very much incomplete.
      - **Based on:**  Qt and C++.
      - You can find its code here: [FSManagementApp](https://github.com/stephen-pinto/POC/tree/main/FSManagementApp)
