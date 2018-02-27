using OpenQA.Selenium;
using OpenQA.Selenium.Chrome;
using System;
using System.Threading;

class EntryPoint
{
    static void Main()
    {
        string url = "http://testing.todvachev.com/selectors/class-name/";
        string className = "testClass";

        IWebDriver driver = new ChromeDriver();

        driver.Navigate().GoToUrl("http://testing.todvachev.com/selectors/class-name/");

        IWebElement element = driver.FindElement(By.ClassName(className));

        Console.WriteLine(element.Text);

        driver.Quit();
    }

    private static void RedMessage(string message)
    {
        Console.ForegroundColor = ConsoleColor.Red;
        Console.WriteLine(message);
        Console.ForegroundColor = ConsoleColor.White;
    }

    private static void GreenMessage(string message)
    {
        Console.ForegroundColor = ConsoleColor.Green;
        Console.WriteLine(message);
        Console.ForegroundColor = ConsoleColor.White;
    }
}