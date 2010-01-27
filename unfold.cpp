/* This short tool is supposed to (roughly) reverse the action done by:
 * 
 * - the standard `fold` tool, which wraps text to a specified line length;
 * - casual authors writing documents at a presentational line length,
 *   in which most of their line breaks are non-semantic.
 * 
 * The reason that this tool should exist is that a lot of plain-text,
 * and almost-plain-text, documents are prematurely formatted.
 * This makes it a rather more complex task to perform operations on
 * the meaningful concepts `sentence' and `paragraph', because (to
 * your script) it is not immediately obvious where one starts and ends,
 * and whether the line breaks in the middle are part of the meaning.
 * 
 * Note that it doesn't understand Windows CR/LF returns; run these
 * files through something like the `fromdos' tool (supplied in the
 * `tofrodos' package in Ubuntu).
 */


#include <iostream>
#include <boost/algorithm/string/trim.hpp>
using namespace std;


enum Linetype {
  blank = 1,     // Line breaks before this ARE meaningful.
  slug,      // Line breaks before this line aren't meaningful
  special    // Like parts of a table, a bullet list, etc.
  };


Linetype determine_linetype(string s) {
  /* Determine whether one given line of input
   * is a real line (return true), or is just a 
   * non-meaningful formatted slug of characters (return false).
   */
  
  string trimmed = boost::algorithm::trim_copy(s);
  
  if(trimmed.length() == 0) {
    return blank;
    }
  
  else if(
      trimmed[0] == '|' ||
      trimmed[0] == '*' ||
      trimmed[0] == '-' ||
      trimmed[0] == '#'
      ) {
    return special;
    }
  
  return slug;
  
  }


int main() {
  
  string current_slug, next_slug;
  enum Linetype current_linetype, next_linetype;
  
  while(cin) {
    getline(cin, next_slug '\n');
    next_linetype = determine_linetype(next_slug);
    
    cout << current_slug;
    
    if(current_linetype == slug && next_linetype == slug) {
      if(current_linetype == slug && current_slug[current_slug.length()-1] != ' ') {
        cout << ' ';
        }
      }
    
    else if(
        (current_linetype == slug || current_linetype == blank || current_linetype == special) &&
        (next_linetype == slug || next_linetype == blank || next_linetype == special)
      ) {
      cout << endl;
      }
    
    current_slug = next_slug;
    current_linetype = next_linetype;
    }
  
  return 0;
  }
