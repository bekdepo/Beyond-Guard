# Beyond-Guard<br>
Open Source Antivirus Suite in C<br>
Creator: Jonathan Chin<br>

This is software is in beta stage and not ready to be used in production yet.<br>

Currently the virus scanner computes an MD5 hash for each file and compares to see if its in the database of virus signatures.
The database has been optimized with an index to find a match in logarithmic time. The virus signatures are
from an open source repository of virus signatures that are actively maintained by malware researchers.  MD5 isn't the best
way to identify a virus as their could be possible collisions, SHA-1 or SHA-256 would be better.
One problem with using a MD5 hash approach to identify viruses is that new viruses that are not in the database cannot be detected,
and even worse they are polymorphic viruses that can change their code thus changing their MD5 hash. A virus can simply insert
blank lines at the end of its code and it will have a new MD5 hash. To get around this another approach would be to have an antivirus
execute a virus in a sandbox(virtual environment) and analyze its behavior for malicious intent. This approach is also problematic
because viruses can also detect if their in a sandbox and refuse to run making it difficult for the virus to analyze its behavior.  
This is where machine learning comes in to train the antivirus to recognize new types of viruses.<br>

Available Features:<br>
1. Command line file scanner that recurses through directories checking when provided a relative or absolute path<br>
2. Database with 27656190 active MD5 virus signatures(not show on github yet).<br>

TODO:<br>
1. Scan registry for malware.<br>
2. Scan running processes for malware.<br>
3. Scan startup for malware.<br>
4. Integrate SHA-1 and SHA-256 hashes to avoid potential false positive MD5 collisions.<br>
5. Real time virus protection, scans all new downloaded files and scan any file before its opened and before it executed.<br>
6. Allow quarantine of suspicious files.<br>
7. Allow removal of viruses in quarantine.<br>
8. Antivirus protection to prevent other worms, malware or virus from killing, damaging or deleting the antivirus.<br>
9. Allow real time antivirus to run on startup.<br>
10. Create installer for easy setup up antivirus and database, allow installer to be downloaded from a web server.<br>
11. Allow virus signatures in database to be updated(need to setup web server to allow users to pull virus new virus signatures.<br>
12. Create GUI to allow non advanced easier navigation as the command line is tedious to some people.<br>
13. Allow antivirus to be able to detect polymorphic viruses by executing them in a sandbox and analyzing its behavior for malicious intent.<br>
14. Allow certain files, folders or processes to be demmed "safe" by user so antivirus can ignore them if a false positive occurs.<br>
15. Unit tests to check integrity of antivirus and to restore/repair database if it has been compromised.<br>
16. Use machine learning to train antivirus to recognize new viruses.<br>
