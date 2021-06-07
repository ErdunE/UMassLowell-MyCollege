Assignment 8: Implementing a Bit of Scrabble with Drag-and-Drop
Assignment Complete Rate: 100%

Full Name: Erdun E
E-mail: Erdun_E@student.uml.edu
Affiliation: Umass Lowell 91.61 GUI Programming 1
Date: 2020-08-12
Web Address: https://erdune.github.io/GUI-Programming-1-HW8/
Reference: https://www.w3schools.com/
Description: This is the html file to create basic format of scrabble slots,
                    word and score place remain, letter tile and rack place remain,
                    reset button with click function. In this assignment, I believe I 
                    complete all parts of "Program Integrity / Design" and "Source
                    Code Documentation and Formatting".I worked second "Extra Credit" part.


Q:Validating to see if a word that the user enters is valid
1.  ajax get resource from words
2.  if ajax success then 
    ```
    var words = result.split("\n");
    for (var i = 0; i < words.length; ++i) {
         dict.push([words[i].toUpperCase()]);
    }
    ```
    push into dict which is an array type
3.  gather word from boardList
    ```
    let word = Board.join().replace(/,/g, "")
    $('#word').html(`<span>${word}</span>`)
    ```
4.   once tile be put into board I will push them into BoardArray like this ['A','C','C','D'];
    then I will check word whether include in the dict like this!
    ```
    for (i = 0; i < dict.length; i++) {
            if (dict[i][0] === word) { // here is check of course when I test this function I //// choose dict[i][0].indexOf(word) > -1 because it will easily to execute
                $('#dictionaryCheckIcon').removeClass('instructionIcon')
                if ($('.instructionIcon').length == 0) {
                    $("#nextWordButton").attr('disabled', false);
                }
            break
        }
    }
    ```
5.  them when click next I will add this score into highest score!
