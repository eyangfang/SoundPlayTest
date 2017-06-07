using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Xunit;
using Moq;
using SoundPlayTest;

namespace UnitTestProject1
{
   // [Collection("AudioWrapperTest")]
    public class MainViewModelTest
    {
        [Fact]
        public void testMehtod()    //Test btnclock_Click();
        {
            var viewModel = new Mock<MainViewModel>();
            MainViewModel obj = viewModel.Object;
            string TextCBtn = obj.BtnCText;
            bool isEnableEbtn = obj.BtnEEnable;
            obj.btnclock_Click();
            Assert.NotEqual(TextCBtn, obj.BtnCText);
            Assert.NotEqual(isEnableEbtn, obj.BtnEEnable);
        }

        [Fact]
        public void testMehtod2()   //Test btnele_Click();
        {
            var viewModel1 = new Mock<MainViewModel>();
            MainViewModel obj1 = viewModel1.Object;
            string TextEBtn = obj1.BtnEText;
            bool isEnableCbtn = obj1.BtnCEnable;
            obj1.btnele_Click();
            Assert.NotEqual(TextEBtn, obj1.BtnEText);
            Assert.NotEqual(isEnableCbtn, obj1.BtnCEnable);
        }

    }
}
