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
    [Collection("AudioWrapperTest")]
    class MainViewModelTest
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
            var viewModel = new Mock<MainViewModel>();
            MainViewModel obj = viewModel.Object;
            string TextEBtn = obj.BtnEText;
            bool isEnableCbtn = obj.BtnCEnable;
            obj.btnele_Click();
            Assert.NotEqual(TextEBtn, obj.BtnEText);
            Assert.NotEqual(isEnableCbtn, obj.BtnCEnable);
        }

    }
}
