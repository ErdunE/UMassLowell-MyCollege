// ADD NEW ITEM TO END OF LIST

var list = document.getElementsByTagName('ul')[0];
var New_Element_1 = document.createElement('li');
var New_Content_1 = document.createTextNode('cream');
New_Element_1.appendChild(New_Content_1);
list.appendChild(New_Element_1);

// ADD NEW ITEM START OF LIST

var New_Element_2 = document.createElement('li');
var New_Content_2 = document.createTextNode('kale');
New_Element_2.appendChild(New_Content_2);
list.insertBefore(New_Element_2, list.childNodes[0]);

// ADD A CLASS OF COOL TO ALL LIST ITEMS

var ListofItems = document.getElementsByTagName('li');
for (var i = 0; i < ListofItems.length; i++)
{
    ListofItems[i].setAttribute('class', 'cool');
}

// ADD NUMBER OF ITEMS IN THE LIST TO THE HEADING

var NumberofItems = ListofItems.length;
var addHeading = '<span>' + NumberofItems + '</span>';
document.getElementsByTagName('h2')[0].innerHTML += addHeading;
