# Collection of Scripts

## xdata2bee.py

A script to convert all xdata ROOT files inside a directory to a zip file that can be uploaded to [Bee](http://www.phy.bnl.gov/wire-cell/bee/)
```bash
python xdata2bee.py [filename] [alg1 alg2 ...]
```
The currently available Wire-Cell algorithms are `simple`, `charge`, `true`, and `mc`.
At the end of the run, a `to_upload.zip` is created and can be drag-to-upload to [Bee](http://www.phy.bnl.gov/wire-cell/bee/)

Some notes:

- The default algorithms to run are `simple`,  `charge`, and `true` if not specified.
- The script expects the ROOT file ending with `_{eventID}.root`,
and will actually run through all files in the same directory that have the same prefix.
- If your files are in the same directory but have different prefix,
you can use a special syntax `python xdata2bee.py 'yourdir/*_*.root' [alg1 alg2 ...]`. Please don't foget the single quotes.

