using OpenQA.Selenium;
using OpenQA.Selenium.Chrome;
using System.Threading;

class EntryPoint
{
    static void Main()
    {
        IWebDriver driver = new ChromeDriver();

        driver.Navigate().GoToUrl("http://testing.todvachev.com/selectors/name/");

        IWebElement element = driver.FindElement(By.Name("myName"));

        if (element.Displayed)
        {
            System.Console.WriteLine("Yes! I can see the element, its right there!");
        }
        else
        {
            System.Console.WriteLine("Well, something went wrong, I couldn't see the element");
        }

        driver.Quit();
    }
}