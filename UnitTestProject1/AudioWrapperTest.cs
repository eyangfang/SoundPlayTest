
using System;
//using Microsoft.VisualStudio.TestTools.UnitTesting;
using SoundPlayTest;
using WindowsRuntimeComponent;
using Xunit;
using Moq;

namespace UnitTestProject1
{
    public class AudioWrapperTest
    {
        enum Orientation
        {
            LEFT,
            RIGHT,
            FRONT,
            BACK,
            TOP,
            BOTTOM
        };
        [Fact]
        public void TestMethod1()
        {
            
        var mock = new Mock<AudioWrapper>();
            AudioWrapper obj = mock.Object;
            Orientation ort = Orientation.LEFT;
            bool clockwise = true;
            obj.SetClockWise(clockwise);
            obj.SetCurrentOrientation((int)ort);
            obj.UpdatePosition();

            Assert.Equal((int)Orientation.FRONT, obj.GetCurrentOrientation());
            
            //bool bstop = obj.Stop();
            //Assert.True(bstop);
        }
    }
}
